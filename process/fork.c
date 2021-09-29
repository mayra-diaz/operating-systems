#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
  int var = 2;
  if (fork() == 0)
  {
	  var++;
	  printf("fork success\n");
  }
    
  
  //printf("New process after fork %d",getpid());  
  printf("var %d pid %d \n", var, getpid());
  sleep(5);
}
