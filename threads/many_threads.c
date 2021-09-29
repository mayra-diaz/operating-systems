#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

#define NUMTHREADS 30000

void* f(void *v){
  printf("Hola thread\n");
  return NULL;
}

int main(){
	pthread_t thr[NUMTHREADS]; 
  
  for (int i = 0; i < NUMTHREADS; ++i) {
    if(pthread_create(&thr[i],NULL,f,NULL) == 0 ){
      printf("pthread sucess\n"); 
    }
  }
  for (int i = 0; i < NUMTHREADS; ++i) {
    pthread_join(thr[i],NULL);
  }
  printf("exit...\n");  
    

  exit(EXIT_SUCCESS);
}
