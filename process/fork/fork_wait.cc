#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
	int pid;
	int status, wait_ret;
	char msg[256];

	sprintf(msg, "hello world");
	pid = fork();

	if( pid == 0 ){                          // Child Process
		printf("pid=%d, %s, child process\n", pid, msg);
		sleep(3);
	} else {                                 // Parent Process
		wait_ret = wait(&status);
		printf("pid=%d, wait_ret=%d, msg=%s, parentprocess\n", pid, wait_ret, msg);
	}

	return 0;
}
