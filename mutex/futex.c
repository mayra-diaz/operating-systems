#include <linux/futex.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

int futex_addr;

/* Retorna -1 if futex have not blocked 
            0 otherwise  */
int futex_wait(void *addr, int val1) {
  return syscall(SYS_futex, addr, FUTEX_WAIT, 
                 val1, NULL, NULL, 0);
}

//returns number of threads just woke up
int futex_wake(void *addr, int n) {
    return syscall(SYS_futex, addr, FUTEX_WAKE, 
                   n, NULL, NULL, 0);
}

void* function_thread0(void *v){
  futex_wait(&futex_addr,0);
  printf("Thread0/n");
  return NULL;
}

void* function_thread1(void *v){
	sleep(7); //emulate waiting
  futex_wake(&futex_addr,1);
  printf("Thread1/n");
  return NULL;
}

int main() {
  
  pthread_t thread0, thread1;
  //int r;
	pthread_create(&thread0, NULL, function_thread0, NULL);
  pthread_create(&thread1, NULL, function_thread1, NULL);
  pthread_join(thread0, NULL);
  pthread_join(thread1, NULL);
  //futex_addr = 0;  
  //r = futex_wait(&futex_addr, 0); 
	//pthread_exit(0);
  //return 0; 
}

