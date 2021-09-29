#include <stdio.h>
#include <pthread.h>

void* function_thread(void *v){
  printf("Create new thread");
  return NULL; 
}


int main()
{
  pthread_t thr;
  pthread_create(&thr,NULL,function_thread,NULL);
  //pthread_join();
  return 0;
}
