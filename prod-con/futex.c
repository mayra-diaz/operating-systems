/*
 * Example 2: FUTEX_WAKE. Thread 0 wakes up N-1 threads.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/syscall.h>
#include <linux/futex.h>

#include <pthread.h>

#include <semaphore.h>
#define N 2
#define N_ITEMS 5

int buffer[N_ITEMS];
int init=0,fin=0;
int cont=0;

/* Return -1 if futex have not blocked and 
            0 otherwise */
int futex_wait(void *addr, int val1) {
  return syscall(SYS_futex, addr, FUTEX_WAIT, 
                 val1, NULL, NULL, 0);
}

/* Return the number of threads running by wake up */
int futex_wake(void *addr, int n) {
    return syscall(SYS_futex, addr, FUTEX_WAKE, 
                   n, NULL, NULL, 0);
}


void* f_prod(void* arg){
  
  for (int i=0; i < N_ITEMS*5; i++){
    while(cont==N_ITEMS)
    	futex_wait(&cont, N_ITEMS);
    
    fin = (fin+1)%N_ITEMS;
    buffer[fin]=i;
    //asm("movl  cont(%rip), %ebx\n"    //cont value to register
	  //"addl    $1, %ebx\n");   // 1 + register
    sleep(random()%3);
    //asm("movl  %ebx, cont(%rip)\n"); //move register to cont
    //cont++;
    __atomic_fetch_add(&cont, 1, __ATOMIC_SEQ_CST);
    if (cont == 1)
      futex_wake(&cont, 1);
  }
}

void* f_cons(void* arg){
  int auxiliar;
  for (int i=0; i < N_ITEMS*5; i++){
    while(cont==0)
    	futex_wait(&cont, 0);
    
    init = (init+1)%N_ITEMS;
    auxiliar=buffer[init];
    
    printf("consumer, item = %d.\n", auxiliar);
    if (auxiliar < i)
      printf("Error: item was consumed before produced.\n");
    else if (auxiliar > i)      
      printf("Error: item was produced before having the free slot.\n");
    
    sleep(random()%3);
    
    __atomic_fetch_add(&cont, -1, __ATOMIC_SEQ_CST);
    //cont--;
    if (cont == N_ITEMS -1)
      futex_wake(&cont, 1);
  }
}

int main() {
  
  for (int i = 0; i < N_ITEMS; i++)
    buffer[i]=-1;
  
	pthread_t thr_prod; 
  pthread_t thr_cons; 
  
  pthread_create(&thr_prod, NULL, f_prod, NULL);
  pthread_create(&thr_cons, NULL, f_cons, NULL);
  
  pthread_exit(0);
  
}
