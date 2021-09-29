//gcc -O0 -S -o optimal_asm_o0.s source.c

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

volatile int s; //s in memory
	
void * f_thread0(void * v) {
	s=0;
  sleep(2);
  printf("Thread 0: %d\n", s);
  return NULL;
}


void * f_thread1(void * v){
  s=1;
  sleep(2);
  printf("Thread 1: %d\n", s);
  return NULL;
}

int main() {
  pthread_t thread_0,thread_1;
  
  for(int i = 0; i < 50; i++) {
    pthread_create(&thread_0, NULL, f_thread0, NULL);
    pthread_create(&thread_1, NULL, f_thread1, NULL);

    pthread_join(thread_0, NULL);
    pthread_join(thread_1, NULL);
  }

  return 0;
}





