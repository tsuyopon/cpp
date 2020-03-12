/*
 * vforkとforkの違いを確認するためのプログラム
 * vforkはUNIX時代の過去の遺物で、子プロセスが終了するまで実質親プロセスは動作しないものらしいです。
 *
 * 参考: http://wiki.bit-hive.com/north/pg/vfork
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <err.h>  

// vforkの場合にはスレッドのようにstatic変数aを共有している。
int a = 0;

int main()
{
       pid_t pid;
       int i;

#ifdef VFORK
	   printf("VFORK START\n");
       pid = vfork();
#else
	   printf("FORK START\n");
       pid = fork();
#endif

       if (pid == 0) {  // 子プロセスの場合
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
