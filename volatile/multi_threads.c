//gcc -O0 -S -o optimal_asm_o0.s source.c
#include <stdio.h>
#include <pthread.h>

volatile int s=0; //s in memory
volatile int lock=0; //lock=free=0;

void* f_thread0() {
  while(lock!=0); //busy wait -  spinlock
  lock=1;
  /* Begin Critical section */
	s=0;
  printf("Thread 0: %d\n", s);
  /* End Critical section */
  
  lock=0;
	return NULL;
}


void* f_thread1(){
  while(lock!=0); //busy wait -  spinlock
  lock=1;
  s=1;
  printf("Thread 1: %d\n", s);
  lock=0;
	return NULL;
}
int main(){
    pthread_t thread_0,thread_1;  //thread_id[100]
    int i;
  	for (i=0;i<100;i++){
    	pthread_create(&thread_0, NULL, f_thread0, NULL);
    	pthread_create(&thread_1, NULL, f_thread1, NULL); 
    } 
    
    
    pthread_join(thread_0, NULL);
  	pthread_join(thread_1, NULL);  
  
    return 0;
}






