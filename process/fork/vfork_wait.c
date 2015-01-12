/*
 * REF: http://wiki.bit-hive.com/north/pg/vfork
 *
 * forkとvforkの違いを理解するためのサンプルプログラム
 * vforkはforkと異なり、子プロセス実行の間は親プロセスは稼働しない。
 * forkとvforkを切り替えて本プログラムを動作させてみてその違いを理解すること
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <err.h>  

int a = 0;

int main()
{
       pid_t   pid;
       int     i;

       pid = vfork();
//       pid = fork();
       if (pid == 0) {
               a = 1;
               for (i = 0; i < 5; i++) {
                       printf("child %d\n", i + 1);
                       sleep(1);
               }
               exit (EXIT_SUCCESS);
       }
       else {
               printf("*data %d\n", a);
               for (i = 0; i < 5; i++) {
                       printf("parent %d\n", i + 1);
                       sleep(1);
               }
               exit (EXIT_SUCCESS);
       }
}
