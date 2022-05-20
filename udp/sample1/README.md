# 概要
UDPで接続を行うプログラム
ポートは22222を使っている。


# send, sendto, sendmsgの違い
- sendはソケットがすでに接続された状態でのみ使用できる。
```
send(sockfd, buf, len, flags);
```

- sendtoはソケットがすでに接続されていなくても、sockaddrやsocklen_tの接続先情報を引き渡す必要がある。sendと比較して最後の2つの引数が追加されていることに注意
```
sendto(sockfd, buf, len, flags, dest_addr, addrlen);
```

- sendmsgは補助データ (制御情報とも呼ばれる) も送付することができる。
  - 1つのパケットを複数のデータに分けることも可能
  - https://linuxjm.osdn.jp/html/LDP_man-pages/man3/cmsg.3.html

# read, readfrom, readmsgの違い
TBD


# コード紹介
以下が受信側(サーバ)のサンプル
- server_recvfrom.c
  - recvfromを使ったサンプル
- server_recvmsg.c
  - recvmsgを使ったサンプル

以下が送信側(クライアント)のサンプル
- client_sendmsg.c 
  - sendmsgを使ったサンプル
- client_sendto.c
  - sendtoを使ったサンプル
