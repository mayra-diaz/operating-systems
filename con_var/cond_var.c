#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock;
pthread_cond_t cv;

volatile int thread0_sleep=0;
volatile int thread1_run=0;

void *f(void * v) {
  pthread_mutex_lock(&lock);
  if (!thread1_run) {
  	printf("Thread0 goes to sleep\n");	
    thread0_sleep=1;
    pthread_cond_wait(&cv ,&lock);
    printf("Thread0 wake up\n");	
  }
	printf("Thread0\n");
  pthread_mutex_unlock(&lock);
  return NULL;
}

void *g(void * v) {
  sleep(5);
	pthread_mutex_lock(&lock);
  if (thread0_sleep) {
  	printf("Thread1 is running\n");	
    thread1_run=1;
    pthread_cond_signal(&cv);
    printf("Thread1 wakes up Thread 0\n");	
  }
	printf("Thread1\n");
  pthread_mutex_unlock(&lock);
  return NULL;
}

int main() {
  pthread_t thread_0, thread_1;
  pthread_mutex_init(&lock, NULL);
  pthread_cond_init(&cv, NULL);
  
  pthread_create(&thread_0, NULL, f, NULL);
  pthread_create(&thread_1, NULL, g, NULL);

	pthread_join(thread_0, NULL);
  pthread_join(thread_1, NULL);
 
  pthread_mutex_destroy(&lock);
  pthread_cond_destroy(&cv);
  return 0;
}