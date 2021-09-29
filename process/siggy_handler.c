#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h>


static void siggy_handler(int signum) //signal handler function
{
  const char *str1= "handled SIGINT";
  const char *str2= "handled SIGQUIT";
  
  switch (signum){
    case SIGINT: //write in stdout a string
    	if (write(STDOUT_FILENO, str1, strlen(str1)) < 0)
        exit(EXIT_FAILURE);
      return;  
    case SIGQUIT: //write in stdout a string
			if (write (STDOUT_FILENO, str2, strlen(str2)) < 0)
        exit(EXIT_FAILURE);
      return;    
    }
}

int main() {
  
  struct sigaction act; //signal library
  act.sa_handler = siggy_handler; //define act
  
  if (sigaction(SIGINT, &act, 0) < 0) //using act as a sig handler
    printf("error on handling SIGINT");
  if (sigaction(SIGQUIT, &act, 0) < 0)
    printf("error on handling SIGQUIT");

 	while(1){
		printf("Hello, World! \n");
    sleep(2);
	}
  return 0;
}
