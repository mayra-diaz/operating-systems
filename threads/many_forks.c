#include <pthread.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#define NUMFORKS 60000

void nothing(){
	unsigned long f=0xff;
}

int main(){
        int pid, status;
	for (int i = 0; i < NUMFORKS; ++i) {
    		switch (pid= fork()){
			case -1:
				printf("fork error");
			case 0:
				nothing();
				exit(EXIT_SUCCESS);
			default:
				waitpid(pid, &status, 0);		
		}
	}
	return 0;
}
