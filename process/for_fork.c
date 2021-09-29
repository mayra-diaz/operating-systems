#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
  printf("-1 pid %d\n",getpid());
  for(int i = 0; i < 3; i++) {
  	fork();
    printf("i %d pid %d \n",i,getpid());
  }
  
  //printf("New process after fork %d",getpid());  
  //printf("var %d pid %d",var,getpid());
  //sleep(5);
}
