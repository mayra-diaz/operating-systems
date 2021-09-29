#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
 
  if (execl("/bin/uname","uname",argv[1], (char *)0) == -1)
    printf("execl uname failed");
  
  printf("execl success");  
}
