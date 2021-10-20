#include <pthread.h>
#include <stdio.h>

pthread_mutex_t lock;

void *f(void* v) {
	pthread_mutex_lock(&lock);
    pthread_mutex_lock(&lock);
    printf("hello world\n");
    return NULL;
}

int main() {
	pthread_mutex_init(&lock, NULL);
    pthread_t thr;
    pthread_create(&thr, NULL, f, NULL);
    pthread_join(thr, NULL);
    return 0;
}