#include <pthread.h>
#include <stdio.h>

void* f(void *v){
  printf("Hola thread\n");
  return NULL;
}


int main(){
	pthread_t thread0;  
  
  if(pthread_create(&thread0,NULL,f,NULL) == 0 ){
    printf("pthread sucess\n"); 
  }
  pthread_join(thread0,NULL);
  printf("exit...\n");  
  return 0;
}
