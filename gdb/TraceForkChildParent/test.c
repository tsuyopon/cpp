// gcc -g test.c 
#include <unistd.h>  // fork
#include <stdlib.h>  // exit

int main(){
	switch(fork())
	{
	  case -1:
		exit(1);
	  case 0:
		//child process,continue
		break;
	  default:
		//the current process,exit
		exit(0);
	}
}
