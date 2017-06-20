/*
 * TCP11111ポートのTCP接続や到達を待つサーバ
 *  TCP接続はlistenのfdを監視して、データ到達はacceptのfdを監視するためにepoll_waitに追加します。
 *
 * [ビルド方法]
 *   $ gcc <file>
 *
 * [実行方法]
 *  $ ./a.out
 *  (メッセージが出力される)
 *
 * 例えば、コマンドラインからだと以下のようなコマンドを指定します。
 * $ telnet localhost 11111
 * (何か入力する)
 */

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/epoll.h>
#include<arpa/inet.h>

#define NEVENTS 16
#define MAX_QUEUE_LISTEN 5

int main(){
	int listenfd, acceptfd;
	struct sockaddr_in addr;
	int epfd;
	struct epoll_event ev, ev_ret[NEVENTS];
	char buf[2048];
	int i;
	int nfds;
	int n;

	socklen_t slen;
	struct sockaddr_in writer_addr;

	// 受信ソケットを２つ作成
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;

	// "127.0.0.1"の部分は必要に応じて変更すること
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

	// 2つの別々のポートで待つために別のポート番号をそれぞれ設定する。
	addr.sin_port = htons(11111);

	// 2つの別々のポートで待つようにbindします。
	bind(listenfd, (struct sockaddr *)&addr, sizeof(addr));

	if(listen(listenfd, MAX_QUEUE_LISTEN) < 0){
		perror("reader: listen");
		close(listenfd);
		return 1;
	}

	epfd = epoll_create(NEVENTS);
	if(epfd < 0){
		perror("epoll_create");
		return 1;
	}

	// listenfdをepoll_waitのイベントに追加する。これでTCP接続を検知できる。
	memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLIN;               // こちらを有効にするとepoll_waitで何度でも検知する。
	//ev.events = EPOLLIN|EPOLLET;     // こちらを有効にするとレベルトリガー(LT)となるので、epoll_waitでは一度しか検知しない。
	ev.data.fd = listenfd;

	if(epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) != 0){
		perror("epoll_ctl");
		return 1;
	}

	// 一度でもTCPデータを受信したらacceptを実行させるためにこのループは終了する
	int count = 0;
	while(1){
		printf("before epoll_wait\n");
		nfds = epoll_wait(epfd, ev_ret, NEVENTS, 1000);  // 1000ms
		if(nfds == 0){
			perror("epoll_wait timeout occured");
		}
	 	printf("after epoll_wait\n");

		for(i=0; i<nfds; i++){
			if(ev_ret[i].data.fd == listenfd){    // TCP接続を受け付けた場合
				printf("TCP RECIEVED!!!!!!!\n");
				count++;
				sleep(1);
			}
		}

		if(count > 3){
			break;
		}
	}

	// acceptを実行して戻り値のfdをepoll_wiatのイベントに追加する。これでデータが到達したことを検知できる。
	slen = sizeof(writer_addr);
	if((acceptfd = accept(listenfd, (struct sockaddr *)&writer_addr, &slen)) < 0){
		perror("reader: accept");
		return 1;
	}

	memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLIN|EPOLLET;
	ev.data.fd = acceptfd;

	if(epoll_ctl(epfd, EPOLL_CTL_ADD, acceptfd, &ev) != 0){
		perror("epoll_ctl");
		return 1;
	}

	// listenfdとacceptfdを両方共検知する。(ただし、listenfdはこの場合すでに一度検知されてしまったので、検知されないようだ)
	while(1){
		printf("before epoll_wait2\n");
		nfds = epoll_wait(epfd, ev_ret, NEVENTS, 1000); // 1000ms
		if(nfds == 0){
			perror("epoll_wait timeout occured");
		}
		printf("after epoll_wait\n");

		for(i=0; i<nfds; i++){
			if(ev_ret[i].data.fd == listenfd){           // TCP接続を受け付けた場合
				printf("TCP RECIEVED!!!!!!\n");
			} else if(ev_ret[i].data.fd == acceptfd){    // データが到達した場合
				printf("DATA RECIEVED!!!!!!\n");
				n = recv(acceptfd, buf, sizeof(buf), 0);
				write(fileno(stdout), buf, n);
			}
		}
		if(nfds > 0){
			return 1;
		}
	}

	close(acceptfd);
	close(listenfd);

	return 0;

}
