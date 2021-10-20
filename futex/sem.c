/*
 * Example 2: FUTEX_WAKE. Thread 0 wakes up N-1 threads.
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

#include <semaphore.h>
#define N 2


sem_t mutex;

void f_thread(void* arg){
  sem_wait(&mutex);     //dec
  print("thread %d in CS\n",arg);
  sleep(3);  //emulate operation in CS
  print("thread %d leaving CS\n",arg);
  sem_post(&mutex);  //inc
}

int main() {
  pthread_t thr[N]; 
  sem_init(&mutex,0,1); //binary semaphore
  
  pthread_create(&thr[0], NULL, f_thread, 0);
  pthread_create(&thr[1], NULL, f_thread, 1);
  
  pthread_exit(0);
  sem_destroy(&mutex);
}
