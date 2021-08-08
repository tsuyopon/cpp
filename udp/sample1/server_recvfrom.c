#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // for close
 
int main(int argc, char** argv)
{
    int sd;
    struct sockaddr_in addr;
 
    socklen_t sin_size;
    struct sockaddr_in from_addr;
 
    char buf[2048]; // 受信バッファ
 
    // IPv4 UDP のソケットを作成
    if((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
 
    // 待ち受けるIPとポート番号を設定
    addr.sin_family = AF_INET;
    addr.sin_port = htons(22222);
    addr.sin_addr.s_addr = INADDR_ANY; // すべてのアドレス宛のパケットを受信する
 
    // バインドする
    if(bind(sd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("bind");
        return -1;
    }
 
    // 受信バッファの初期化
    memset(buf, 0, sizeof(buf));
 
    // 受信 パケットが到着するまでブロック
    // from_addr には、送信元アドレスが格納される
    int i = 0;
    while(1){
        if(recvfrom(sd, buf, sizeof(buf), 0,
                    (struct sockaddr *)&from_addr, &sin_size) < 0) {
            perror("recvfrom");
            return -1;
        }
         // 受信データの出力
         printf("%d: %s\n", i++, buf);
//        sleep(1);
    }
 
    // ソケットのクローズ
    close(sd);
 
    return 0;
}
