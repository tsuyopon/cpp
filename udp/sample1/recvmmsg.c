//
// (注意点) recvmmsgシステムコールはLinux以外ではコンパイルできないことに注意してください。
//  see: https://linuxjm.osdn.jp/html/LDP_man-pages/man2/recvmmsg.2.html
//       https://blog.tjun.org/entry/2014/02/08/recvmmsg%E3%81%AB%E3%81%A4%E3%81%84%E3%81%A6
//
//  recvmsgと比較したrecvmmsgとの違い
//   - 複数個を受け取ることができる
//   - timeoutをとれる
//
#define _GNU_SOURCE
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define VLEN 10
#define BUFSIZE 200
#define TIMEOUT 5

int  main(void)  {

  int sockfd, retval, i;
  struct sockaddr_in sa;
  struct mmsghdr msgs[VLEN];
  struct iovec iovecs[VLEN];
  char bufs[VLEN][BUFSIZE+1];
  struct timespec timeout;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1) {
    perror("socket()");
    exit(EXIT_FAILURE);
  }

  sa.sin_family = AF_INET;
  sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  sa.sin_port = htons(22222);
  if (bind(sockfd, (struct sockaddr *) &sa, sizeof(sa)) == -1) {
    perror("bind()");
    exit(EXIT_FAILURE);
  }

  memset(msgs, 0, sizeof(msgs));
  for (i = 0; i < VLEN; i++) {
    iovecs[i].iov_base = bufs[i];
    iovecs[i].iov_len = BUFSIZE;
    msgs[i].msg_hdr.msg_iov = &iovecs[i];
    msgs[i].msg_hdr.msg_iovlen = 1;
  }

  // recvmmsgは以下でタイムアウト値を設定できるので、値を大きくしてクライアントから大量のパケットを送って、一括受信できるかテストすることが可能
  timeout.tv_sec = TIMEOUT;
  timeout.tv_nsec = 0;

  // 一気にUDPパケットを受信してからrecvmmsgを実行すると一括で受け取ることができます。(最大はVLENで指定した10パケット まで)
  /*
   * また、recvmmsgがすぐに抜けてきて欲しいときに timeoutに0 (tvsec=0, tvnsec=0) をセットすると、1つrecvしただけで返ってきてしまうのも注意。
   * すぐに抜けて来て欲しいけど、そのときに取れるmessageは全て取りたい、という時には、flagに MSG_DONTWAIT をセットして、timeoutはNULLにして呼び出すと期待している動作になります。
   */
  retval = recvmmsg(sockfd, msgs, VLEN, 0, &timeout);
  if (retval == -1) {
    perror("recvmmsg()");
    exit(EXIT_FAILURE);
  }

  printf("%d messages received\n", retval);
  for (i = 0; i < retval; i++) {
    bufs[i][msgs[i].msg_len] = 0;
    printf("%d %s", i+1, bufs[i]);
  }

  exit(EXIT_SUCCESS);
}
