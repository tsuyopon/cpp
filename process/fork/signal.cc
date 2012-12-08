#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

void signal_handler(int sig){

	printf("RECIEVED signal number=%d\n", sig);
	exit(EXIT_SUCCESS);
}

int main(void){
 	signal(SIGINT, signal_handler);   // Output if Enter "Ctrl + C"
	signal(SIGKILL, signal_handler);   // Output if Kill Signal 
	signal(SIGALRM, signal_handler);
	while(1);
	return 0;
}
