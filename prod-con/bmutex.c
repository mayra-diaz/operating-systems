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
#define N_ITEMS 5

int buffer[N_ITEMS];
int init=0,fin=0;
int cont=0;

void* f_prod(void *arg){
  
  for (int i=0; i < N_ITEMS*3; i++){
    while(cont==N_ITEMS);
    
    fin = (fin+1)%N_ITEMS;
    buffer[fin]=i;
    sleep(random()%3);
    cont++;
  }
  return NULL;
}

void* f_cons(void *arg){
  int auxiliar;
  for (int i=0; i < N_ITEMS*3; i++){
    while(cont==0);
    
    init = (init+1)%N_ITEMS;
    auxiliar=buffer[init];
    
    printf("consumer, item = %d.\n", auxiliar);
    if (auxiliar < i)
      printf("Error: item was consumed before produced.\n");
    else if (auxiliar > i)      
      printf("Error: item was produced before having the free slot.\n");
    
    sleep(random()%3);
    cont--;
  }
  return NULL;
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
