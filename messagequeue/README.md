# 概要
共有メモリとは別にメッセージキューを用いる

# 使い方
makeコマンドでserverとclientという２つの実行ファイルを生成してくれます。
```
$ make
```

serverを起動してからclientを実行するとただのechoサーバに見えてしまうのでまずはclientを３回ほど実行してみます。
```
$ ./client 
Enter message: hoge1
$ ./client 
Enter message: hoge2
$ ./client 
Enter message: hoge3
```

続いて、ipcsコマンドを叩いてみると先ほど実行したclientの３件のキューが溜まっていることが確認できます。
```
$ ipcs

------ Shared Memory Segments --------
key        shmid      owner      perms      bytes      nattch     status      

------ Semaphore Arrays --------
key        semid      owner      perms      nsems     

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0xffffffff 0          tsuyoshi   666        768          3    
```

ここでserverを動かすと一気に溜まったキューを処理します。
```
$ ./server 
message received from 6583
hoge1
message received from 6584
hoge2
message received from 6585
hoge3
```

# 参考URL
- http://www.geocities.co.jp/Athlete-Samos/7760/study/msgkyu1.html
