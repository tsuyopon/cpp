/*
 * シグナルドリブンによるepoll_waitの解除
 *
 * コンパイル $ gcc <file>
 *
 * 片方の端末で実行すると次の状態でプロンプトが停止します。
 * $ ./a.out 
 * before epoll_wait
 *
 * その後、上記の状態で別のターミナルを開いてSIGUSR1を与えると./a.outが再開します。
 * $ kill -USR1 <PID>
 *
 * 本プログラムでは2度SIGUSR1を受け取ると終了します。
 */

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>
#include<sys/epoll.h>

#define NEVENTS 16

void sigusr1_handler(int sig){
	write(fileno(stdout), "signal called\n", 14);
}

int main(){
	int nfds;
	int epfd;

	// SIGUSR1のシグナルハンドラを設定する
	signal(SIGUSR1, sigusr1_handler);

	epfd = epoll_create(NEVENTS);
	if(epfd < 0 ){
		perror("epoll_create error");
		return 1;
	}

	printf("before epoll_wait\n");

	// SIGUSR1が来るまでepoll_waitはブロックし続ける
	nfds = epoll_wait(epfd, NULL, NEVENTS, -1);
	printf("after epoll_wait : %d\n", nfds);

	nfds = epoll_wait(epfd, NULL, NEVENTS, -1);
	printf("after epoll_wait: %d\n", nfds);

	// errnoがEINTRになっているのを確認する
	printf("%d\n", errno);
	perror("perror after epoll_wait");
}
