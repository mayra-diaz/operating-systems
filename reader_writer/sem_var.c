
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NL 10
#define NE 3

sem_t sem_bd;
volatile int bd = -1; /* data base */

sem_t sem_nr;
volatile int nl = 0;

void *reader(void* v) {
  int id = *((int*)(&v));

  sem_wait(&sem_nr); //
  nl++;
  if (nl == 1)
    sem_wait(&sem_bd);
  sem_post(&sem_nr);
  printf("reader %d read value %d \n", id, bd);
  sleep(1);
  sem_wait(&sem_nr);
  nl--;
  if (nl == 0)
    sem_post(&sem_bd);
  sem_post(&sem_nr);
  return NULL;
}

void *writer(void *v) {
  int id = *((int*)(&v));
  
  sem_wait(&sem_bd);
  bd = id;
  sleep(1);
  printf("writer %d wrote value %d \n", id, bd);
  sem_post(&sem_bd);

  return NULL;
}

#define N 300
int main() {
  pthread_t thr[N];
  int i = 0, l = 0, e = 0;

  sem_init(&sem_bd, 0, 1);
  sem_init(&sem_nr, 0, 1);
  
  for (i = 0; i < N; i++) {
    if (random() % 2) 
      pthread_create(&thr[i], NULL, reader, (void*) l++);
    else
      pthread_create(&thr[i], NULL, writer, (void*) e++);
  }

  pthread_exit(NULL);
}