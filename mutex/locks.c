#include <pthread.h>
#include <stdio.h>

int lock_value=0;
    
void lock(){
  int return_value;
	while( (return_value = __sync_val_compare_and_swap(&lock_value,0,1)) != 0);
}

void unlock(){
	lock_value=0;
}

void* t1(void* v){
  lock();
  printf("thread 1\n");
  unlock();
  return NULL;
}

void* t2(void* v){
  lock();
  printf("thread 2\n");
  unlock();
  return NULL;	
}

int main(){
  pthread_t thr[2];
  
  pthread_create(&thr[0], NULL, &t1, NULL);
  pthread_create(&thr[1], NULL, &t2, NULL);
  pthread_join(thr[0], NULL);
  pthread_join(thr[1], NULL);
  return 0;
}