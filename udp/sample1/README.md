# 概要
UDPで接続を行うプログラム
ポートは22222を使っている。

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
