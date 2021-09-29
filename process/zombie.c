#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(void)
{
	pid_t pid;
	pid = fork();

	if (pid<0){
		fprintf(stderr, "Unable to create child process");
		return -1;
	}
	else if(pid==0)
		return 0;
	else {
		sleep(5);
		printf("Parent finish\n");
		return 0;
	}
}
