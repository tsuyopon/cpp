# 概要
DNSクライアント(UDP)のサンプルプログラム
- プログラムはAレコードを引く
- サーバは固定となっている

# サンプルレスポンス
```
$ gcc dnsclient.c
$ ./a.out 
Enter Hostname to Lookup : www.yahoo.co.jp
Resolving www.yahoo.co.jp
Sending Packet...Done
Receiving answer...Done
The response contains : 
 1 Questions.
 2 Answers.
 0 Authoritative Servers.
 0 Additional records.


Answer Records : 2 
Name : www.yahoo.co.jp has alias name : edge.g.yimg.jp
Name : edge.g.yimg.jp has IPv4 address : 182.22.24.124

Authoritive Records : 0 

Additional Records : 0 
```

