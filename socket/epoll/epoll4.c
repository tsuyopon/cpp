//  
/*
 * epollによる並列処理
 *
 * [プログラム説明]
 * TCPサーバとして、イベントを次のようにして扱っている。
 * 1. socket用のイベントをsock0をepoll_ctlで追加して
 * 2. epoll_waitのループに入る
 * 3. 接続があれば、
 *   3.1 fd===sock0のif文に入って、read用のイベントをepoll_ctlで追加(ADD)する。
 *   3.2 epoll_waitで処理が帰ってきて、続いてreadの処理が行われる。
 *   3.3 その後、write用のイベントをepoll_ctlで修正(MOD)する。
 *   3.4 epoll_waitで処理が帰ってきて、続いてwriteの処理が行われる。
 *   3.5 writeの処理が終わったらepoll_ctlでイベントを削除(DEL)する。
 * 4. epoll_waitで次の接続処理が来るまで待つ。
 *
 * 参考 http://www.geekpage.jp/programming/linux-network/book/10/10-3.php
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <errno.h>

#define NEVENTS 16
#define BUFSIZE 1024

enum mystate {
  MYSTATE_READ = 0,
  MYSTATE_WRITE
};

int
main()
{
  int sock0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  socklen_t len;
  int sock;
  int n, i;
  struct epoll_event ev, ev_ret[NEVENTS];
  int epfd;
  int nfds;
  struct clientinfo {
    int fd;
    char buf[1024];
    int n;
    int state;
  };

  /* (1) */
  /* ソケットの作成 */
  sock0 = socket(AF_INET, SOCK_STREAM, 0);
  /* ソケットの設定 */
  addr.sin_family = AF_INET;
  addr.sin_port = htons(12345);
  addr.sin_addr.s_addr = INADDR_ANY;
  bind(sock0, (struct sockaddr *)&addr, sizeof(addr));
  listen(sock0, 5);       // この状態でpsコマンドでLISTENとなる。

  /* (2) */
  epfd = epoll_create(NEVENTS);
  if (epfd < 0) {
    perror("epoll_create");
    return 1;
  }
  /* (3) */
  memset(&ev, 0, sizeof(ev));
  ev.events = EPOLLIN;
  ev.data.ptr = malloc(sizeof(struct clientinfo));
  if (ev.data.ptr == NULL) {
    perror("malloc");
    return 1;
  }
  memset(ev.data.ptr, 0, sizeof(struct clientinfo));
  ((struct clientinfo *)ev.data.ptr)->fd = sock0;
  if (epoll_ctl(epfd, EPOLL_CTL_ADD, sock0, &ev) != 0) {    // epoll_ctlでADD
    perror("epoll_ctl");
    return 1;
  }
  /* (4) */
  for (;;) {
    nfds = epoll_wait(epfd, ev_ret, NEVENTS, -1);      // epoll_waitの戻り値はファイルディスクリタの数を表す
    if (nfds < 0) {
      perror("epoll_wait");
      return 1;
    }

    /* (5) */
    printf("after epoll_wait : nfds=%d＼n", nfds);

	// epoll_waitで検出したイベントの数だけループする
    for (i=0; i<nfds; i++) {

      struct clientinfo *ci = ev_ret[i].data.ptr;
      printf("fd=%d＼n", ci->fd);

	  // sock0はsocket関数から帰ってくるファイルディスクリプタが変化した場合
      if (ci->fd == sock0) {
        /* (6) */
        /* TCPクライアントからの接続要求を受け付ける */
        len = sizeof(client);
        sock = accept(sock0, (struct sockaddr *)&client, &len);
        if (sock < 0) {
          perror("accept");
          return 1;
        }

        printf("accept sock=%d＼n", sock);

        memset(&ev, 0, sizeof(ev));
        ev.events = EPOLLIN | EPOLLONESHOT;
        ev.data.ptr = malloc(sizeof(struct clientinfo));
        if (ev.data.ptr == NULL) {
          perror("malloc");
          return 1;
        }

        memset(ev.data.ptr, 0, sizeof(struct clientinfo));
        ((struct clientinfo *)ev.data.ptr)->fd = sock;

        if (epoll_ctl(epfd, EPOLL_CTL_ADD, sock, &ev) != 0) {    // epoll_ctlでADDする
          perror("epoll_ctl");
          return 1;
        }

      } else {
        /* (7) */
		// acceptから接続されてきたデータが読み取り可能になった場合
        if (ev_ret[i].events & EPOLLIN) {
          ci->n = read(ci->fd, ci->buf, BUFSIZE);
          if (ci->n < 0) {
            perror("read");
            return 1;
          }

          ci->state = MYSTATE_WRITE;
          ev_ret[i].events = EPOLLOUT;

          if (epoll_ctl(epfd, EPOLL_CTL_MOD, ci->fd, &ev_ret[i]) != 0) {    // epoll_ctlでMOD
            perror("epoll_ctl");
            return 1;
          }
        } else if (ev_ret[i].events & EPOLLOUT) {
          /* (8) */
		  // acceptから接続されてきたデータが書き込み可能になった場合
          n = write(ci->fd, ci->buf, ci->n);
          if (n < 0) {
            perror("write");
            return 1;
          }

          if (epoll_ctl(epfd, EPOLL_CTL_DEL, ci->fd, &ev_ret[i]) != 0) {  // epoll_ctlでDEL
            perror("epoll_ctl");
            return 1;
          }

          close(ci->fd);
          free(ev_ret[i].data.ptr);
        }
      }
    }
  }

  /* (9) */
  /* listen するsocketの終了 */
  close(sock0);

  return 0;
}
