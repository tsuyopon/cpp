#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <err.h>  

int main()
{
       pid_t pid = fork();
       if (pid == 0) {  // 子プロセスの場合
               printf("Hello world");
				sleep(10);
       }
       else {
               printf("Hello main");
				sleep(10);
       }
}

