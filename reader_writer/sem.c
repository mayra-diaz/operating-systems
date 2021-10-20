/*
 * Reader writer semaphore
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int bd = -1; /* Data base */
sem_t sem_bd;

void *reader(void* v) {
  int id = *((int*)(&v));

  sem_wait(&sem_bd);
  sleep(1);
  printf("reader %d read the value %d \n",id, bd);
  sem_post(&sem_bd);
  
  return NULL;
}

void *writer(void *v) {
  int id = *((int*)(&v));
  
  sem_wait(&sem_bd);
  bd = id;
  sleep(1);
  printf("writer %d wrote the value %d \n", id, bd);
  sem_post(&sem_bd);

  return NULL;
}

#define N 60
int main() {
  pthread_t thr[N];
  int i = 0, l = 0, e = 0;

  sem_init(&sem_bd, 0, 1);
  for (i = 0; i < N; i++) {
    if (random() % 2) 
      pthread_create(&thr[i], NULL, reader, (void*) l++);
    else
      pthread_create(&thr[i], NULL, writer, (void*) e++);
  }

  pthread_exit(NULL);
}

