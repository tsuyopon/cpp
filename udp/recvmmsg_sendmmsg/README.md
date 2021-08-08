# 概要
recvmmsgとsendmmsgはLinuxでのみ使えるシステムコールです。

# 使い方
あらかじめrecvmmsgを起動しておきます。
```
# ./recvmmsg 
```

メッセージを送付します。
```
# ./sendmmsg
```

出力されます。
```
# ./recvmmsg 
3 messages received
1 onetwo
2 three
3 onetwo
```
