/*
 * Example 2: FUTEX_WAKE. Thread 0 wakes up N-1 threads.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <linux/futex.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <limits.h>

#define N 2

int futex_addr = 0;

int lock_value=0;

/* Retorna -1 if futex have not blocked and
            0 otherwise */
int futex_wait(void *addr, int val1) {
  return syscall(SYS_futex, addr, FUTEX_WAIT, 
                 val1, NULL, NULL, 0);
}

/* Returns the number of running threads (just woke up) */
int futex_wake(void *addr, int n) {
    return syscall(SYS_futex, addr, FUTEX_WAKE, 
                   n, NULL, NULL, 0);
}

void lock(){
  int aux;
  while ((aux = __sync_val_compare_and_swap(&lock_value, 0, 1)) != 0) {
    futex_wait(&lock_value,1);
  }
}
  
void unlock(){
  lock_value = 0;
  futex_wake(&lock_value,1);
}

void* f_thread0(void *v) {
	lock();
  printf("Thread 0\n");  
  sleep(1);
  unlock();
  return NULL;
}

void* f_thread1(void *v) {
	lock();
  printf("Thread 1\n");  
  sleep(2);
  unlock();
  return NULL;
}

int main() {
  pthread_t thr[N]; 
  int i;
  
  //for (i=1; i < N; i++)
    //pthread_create(&thr[i], NULL, f_thread, (void*) i);
  pthread_create(&thr[0], NULL, f_thread0, NULL);
  pthread_create(&thr[1], NULL, f_thread1, NULL);
  
  pthread_exit(0);
}
