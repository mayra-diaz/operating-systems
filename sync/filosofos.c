/*
 * Solution with deadlock... :(
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 5
#define N_CYCLES 8
     
sem_t sem_fork[N];

/* Extra variables to show the status of the table*/
sem_t sem_table;
enum pos_fork {LEFT, TABLE, RIGHT} pos_fork[N];
char table[4*N+1];

/*
 *  fork left = phil_id
 *  fork right = (phil_id + 1) % N
 */

void print() {
  printf("%s%c%c\n", &table[1], table[0], table[1]);
}

void stay_starve(int phil_id) {
  sem_wait(&sem_table);
  table[4 * phil_id + 3] = 'H';
  print();
  sem_post(&sem_table);
  sleep(1);
}

void eat(int phil_id) {
  sem_wait(&sem_table);
  table[4 * phil_id + 3] = 'E';
  print();
  sem_post(&sem_table);
  sleep(1);
}

void take_fork_left(int phil_id) {
  sem_wait(&sem_fork[phil_id]);
  sem_wait(&sem_table);
  table[4 * phil_id] = ' ';
  table[4 * phil_id + 1] = ' ';
  table[4 * phil_id + 2] = '|';
  print();
  sem_post(&sem_table);
  sleep(1);
}  

void take_fork_right(int phil_id) {
  int right = (phil_id + 1) % N;
  sem_wait(&sem_fork[right]);
  sem_wait(&sem_table);
  table[4 * right] = '|';
  table[4 * right + 1] = ' ';
  table[4 * right + 2] = ' ';
  print();
  sem_post(&sem_table);

}

void release_forks_think(int phil_id) {
  int right = (phil_id + 1) % N;
  sem_wait(&sem_table);
  sem_post(&sem_fork[right]);
  sem_post(&sem_fork[phil_id]);
  table[4 * phil_id] = ' ';
  table[4 * phil_id + 1] = '-';
  table[4 * phil_id + 2] = ' ';
  table[4 * right] = ' ';
  table[4 * right + 1] = '-';
  table[4 * right + 2] = ' ';
  table[4 * phil_id + 3] = 'T';
  print();
  sem_post(&sem_table);
  sleep(1);
}


void* f_phil(void *v) {
  int phil_id = *(int *) v;
  int i;


  for (i = 0; i < N_CYCLES; i++) {
    stay_starve(phil_id);
    
    take_fork_right(phil_id);
    take_fork_left(phil_id);

    eat(phil_id);
	
    release_forks_think(phil_id);
  }
  
  return NULL;
}

int main() {
  pthread_t thr[N];
  int i, phil_id[N];

  sem_init(&sem_table, 0, 1);
  for (i = 0; i < N; i++) {
      sem_init(&sem_fork[i], 0, 1);
      pos_fork[i] = TABLE;
      table[4 * i] = ' ';
      table[4 * i + 1] = '-';
      table[4 * i + 2] = ' ';
      table[4 * i + 3] = 'T';
  }

  table[4*N+1] = 0;

  for (i = 0; i < N; i++) {
    phil_id[i] = i;
    pthread_create(&thr[i], NULL, f_phil, (void*) &phil_id[i]);
  }

  for (i = 0; i < N; i++) 
    pthread_join(thr[i], NULL);

  for (i = 0; i < N; i++) 
    sem_destroy(&sem_fork[i]);
  sem_destroy(&sem_table);
    
  return 0;
}
