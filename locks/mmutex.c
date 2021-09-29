#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock;

void* t(void* i){
  pthread_mutex_lock(&lock);
  printf("thread ");
  printf(i);
  printf("\n");
  pthread_mutex_unlock(&lock);
  return NULL;
}


int main(){
    int n = 10;
    pthread_t thr[n];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < n; i++)
        pthread_create(&thr[i], NULL, &t, &i);

    pthread_mutex_destroy(&lock);
    for (size_t i = 0; i < n; i++)
        pthread_join(thr[i], NULL);
    return 0;
}