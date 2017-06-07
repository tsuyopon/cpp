/*
 * socket接続(UDP)ドリブンによるepoll_waitの解除
 * UDPなのでlistenやacceptは存在しない
 *
 * ビルド方法: $ gcc <file>
 *
 * 実行方法
 * $ ./a.out
 * (メッセージが出力される)
 *
 * その後、UDPの11111または22222ポートのいずれかで接続すると処理が終了します。
 *
 * 例えば、コマンドラインからだと次のようなコマンドを発行します。
 * $ echo "This is a test" | nc -u localhost 1111
 *
 * [補足] epoll2client.cというクライアント接続用ファイルがありますが、これを使わずにncでもよい
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

int main(){
	int sock1, sock2;
	struct sockaddr_in addr1, addr2;
	int epfd;
	struct epoll_event ev, ev_ret[NEVENTS];
	char buf[2048];
	int i;
	int nfds;
	int n;

	// 受信ソケットを２つ作成
	sock1 = socket(AF_INET, SOCK_DGRAM, 0);
	sock2 = socket(AF_INET, SOCK_DGRAM, 0);
	addr1.sin_family = AF_INET;
	addr2.sin_family = AF_INET;

	// 127.0.0.1の部分は必要に応じて変更すること
	inet_pton(AF_INET, "127.0.0.1", &addr1.sin_addr.s_addr);
	inet_pton(AF_INET, "127.0.0.1", &addr2.sin_addr.s_addr);

	// 2つの別々のポートで保つために別のポート番号をそれぞれ設定します。
	addr1.sin_port = htons(11111);
	addr2.sin_port = htons(22222);

	// 2つの別々のポートで待つようにbindする
	bind(sock1, (struct sockaddr *)&addr1, sizeof(addr1));
	bind(sock2, (struct sockaddr *)&addr2, sizeof(addr2));

	epfd = epoll_create(NEVENTS);
	if(epfd < 0){
		perror("epoll_create");
		return 1;
	}

	memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLIN;
	ev.data.fd = sock1;
	if(epoll_ctl(epfd, EPOLL_CTL_ADD, sock1, &ev) != 0 ){
		perror("epoll_ctl");
		return 1;
	}

	memset(&ev, 0, sizeof(ev));
	ev.events = EPOLLIN;
	ev.data.fd = sock2;
	if(epoll_ctl(epfd, EPOLL_CTL_ADD, sock2, &ev) != 0 ){
		perror("epoll_ctl");
		return 1;
	}

	while(1) {

		printf("before epoll_wait\n");
		nfds = epoll_wait(epfd, ev_ret, NEVENTS, 1000);   // 1000ms
		if(nfds == 0){
			perror("epoll_wait timeout occured");
		}
		printf("after epoll_wait\n");
		for(i=0; i< nfds; i++){
			if(ev_ret[i].data.fd == sock1){
				printf("sock1 recieved\n");
				// sock1に読み込み可能データがある場合、sock1からデータを受信して表示する
				n = recv(sock1, buf, sizeof(buf), 0);
				write(fileno(stdout), buf, n);
			} else if(ev_ret[i].data.fd == sock2){
				printf("sock2 recieved\n");
				// sock2に読み込み可能データがある場合、sock2からデータを受信して表示する
				n = recv(sock2, buf, sizeof(buf), 0);
				write(fileno(stdout), buf, n);
			}
		}
	}
	if(nfds > 0){
		return 1;
	}

	close(sock1);
	close(sock2);

	return 0;


}
