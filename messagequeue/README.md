# 概要
共有メモリとは別にメッセージキューを用いる。msgget, msgrcv, msgsnd関数などを使ったMQはSystem Vメッセージキューなどと呼ばれます。  
POSIX MQと同じような機能を提供するが以下の点で異なっています。
- Posixメッセージキューからの読み出しは、常に最も高い優先度の最も古いメッセージを返す。System V メッセージキューでは、任意の優先度のメッセージを読み出すことが出来る。
- Posixメッセージキューでは、空のキューにメッセージが置かれた際にシグナルの生成やスレッドの起動が行えるが、System V メッセージキューでは、このような操作が行えない。

- (参考リンク)[http://d.hatena.ne.jp/s-kita/20080713/1215940088]
 

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
