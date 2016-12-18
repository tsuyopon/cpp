# 概要
POSIX MQはLinuxKernel-2.6.6以降でサポートされている。
```
mq_open          メッセージキューを開く。
mq_getattr       メッセージキューの属性を取得する。
mq_setattr       メッセージキューの属性を設定する。 
mq_send          メッセージキューにメッセージを送信する。
mq_receive       メッセージキューからメッセージを受信する。
mq_notify        メッセージ到着時に通知を行うように登録する。
mq_timedsend     タイムアウト時刻指定できるmq_send
mq_timedreceive  タイムアウト時刻指定できるmq_receive 
mq_close         メッセージキューを閉じる。
mq_unlink        メッセージキューを削除する。
```

# 参考
- コード参考
 - http://stackoverflow.com/questions/3056307/how-do-i-use-mqueue-in-a-c-program-on-a-linux-based-system
- MQ\_OVERVIEW
 - https://linuxjm.osdn.jp/html/LDP_man-pages/man7/mq_overview.7.html
