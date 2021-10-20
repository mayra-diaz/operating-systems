#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock;
pthread_cond_t cv;

volatile int n_threads_sleeping=0;
volatile int thread0_run=0;

void *thread0(void *v){
  sleep(5);
  
  pthread_mutex_lock(&lock);
  for (int j=n_threads_sleeping; j>0; j--){
   	pthread_cond_signal(&cv); 
  }
	
  pthread_mutex_unlock(&lock);
  return NULL;
}

void *f(void *v){ //sleeping thread
  //sleep(random()%2);
  
  pthread_mutex_lock(&lock);
  
  if (thread0_run==0){
    n_threads_sleeping++;
    printf("thread %d sleep\n", *(int *)v);
    pthread_cond_wait(&cv,&lock);
    n_threads_sleeping--;
  }
  printf("thread %d out\n", *(int*)v);
  pthread_mutex_unlock(&lock);
  return NULL;
}

int main() {
  pthread_t thread_0, thread[4];
  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&cv, NULL);
  int id[4] = {1, 2, 3, 4};
  
  pthread_create(&thread_0, NULL, thread0, 0);
  for(int i=0; i < 4; i++)
  	pthread_create(&thread[i], NULL, f, &id[i]);

  pthread_join(thread_0, NULL);
  for(int i=0; i < 4; i++)
  	pthread_join(thread[i], NULL);
 
  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&cv);
  return 0;
}