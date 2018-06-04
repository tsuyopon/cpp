// HTTPへの送信及び受信を行う単純なプログラムです。
// $ gcc http_sample.c
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int
main()
{
 struct sockaddr_in server;
 int sock;
 char packet_bytes[] = "GET /\n";   // GETリクエストを指定
 char buf[10000];
 int n;

 /* ソケットの作成 */
 sock = socket(PF_INET, SOCK_STREAM, 0);

 /* 接続先指定用構造体の準備 */
 server.sin_family = PF_INET;
 server.sin_port = htons(80);
 server.sin_addr.s_addr = inet_addr("127.0.0.1");
 //server.sin_addr.s_addr = inet_addr("182.22.25.124");  // yahoo japan

 /* サーバに接続 */
 connect(sock, (struct sockaddr *)&server, sizeof(server));

 /* サーバへデータを送信 */
 write(sock, packet_bytes, sizeof(packet_bytes));

 /* サーバからデータを受信 */
 memset(buf, 0, sizeof(buf));
 n = read(sock, buf, sizeof(buf));
 printf("%s\n", buf);

 /* socketの終了 */
 close(sock);

 return 0;
}
