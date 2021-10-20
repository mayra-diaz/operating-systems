#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock;

void* t1(void* v){
  pthread_mutex_lock(&lock);
  printf("thread 1\n");
  pthread_mutex_unlock(&lock);
  return NULL;
}

void* t2(void* v){
  pthread_mutex_lock(&lock);
	printf("thread 2\n");
  pthread_mutex_unlock(&lock);
  return NULL;	
}

int main(){
	pthread_t thr[2];
  pthread_mutex_init(&lock,NULL);
  
  pthread_create(&thr[0], NULL, &t1, NULL);
  pthread_create(&thr[1], NULL, &t2, NULL);
  pthread_mutex_destroy(&lock);
  pthread_join(thr[0], NULL);
  pthread_join(thr[1], NULL);
  return 0;
}