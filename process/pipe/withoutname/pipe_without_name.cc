/*
 * Send Message Program From Child Process Into Parent Process using Pipe without name.
 * Without name Pattern is used by only parent and child relations.
 *
 * Example
 *    $ ls -alt | xargs echo
 * "ls -alt" is processed by child process. and "xargs echo" is processed by parent process.
 *
 * See Below URL For Reference.
 *     http://www.geocities.jp/sugachan1973/doc/funto45.html
 */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(void){
	pid_t pid;
	char buffer[256];
	int pp[2];

	// Creating Pipe
	pipe(pp);

	// Creatig Child Process
	pid = fork();

	if( pid == 0 ){   // Child Process
		close(pp[0]);
		fgets(buffer, 256, stdin);
		write(pp[1], buffer, strlen(buffer)+1);   // Write Into Pipe
	} else {          // Parent Process
		close(pp[1]);
		read(pp[0], buffer, 256);                 // Read From Pipe
		printf("Message From Child: %s\n", buffer);
		close(pp[0]);
	}
	return 0;
}
