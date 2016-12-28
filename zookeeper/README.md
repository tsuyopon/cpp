# 概要
zookeeperを使ったサンプルライブラリについて

# zookeeperを動かしてみる
プログラムを動作させる前にあらかじめスタンドアロンとしてzookeperサーバを動かしておく必要がある。
- https://zookeeper.apache.org/doc/r3.1.2/zookeeperStarted.html
```
$ wget http://ftp.jaist.ac.jp/pub/apache/zookeeper/zookeeper-3.4.9/zookeeper-3.4.9.tar.gz
$ tar zxvf zookeeper-3.4.9.tar.gz
$ cd zookeeper-3.4.9
$ vim conf/zoo.cfg
tickTime=2000
dataDir=/var/zookeeper
clientPort=2181
$
$ sudo ./bin/zkServer.sh start
/usr/bin/java
ZooKeeper JMX enabled by default
Using config: /Users/tsuyoshi/SOURCE/zookeeper/bin/../conf/zoo.cfg
Starting zookeeper ... STARTED
$
$ ps auxww | grep -i zookeeper
root            4353   0.0  0.6  3735684  25976 s006  S    12:31PM   0:00.33 /usr/bin/java -Dzookeeper.log.dir=/Users/tsuyoshi/SOURCE/zookeeper/bin/../logs -Dzookeeper.log.file=zookeeper-root-server-tsuyoshi.local.log -Dzookeeper.root.logger=INFO,CONSOLE -XX:+HeapDumpOnOutOfMemoryError -XX:OnOutOfMemoryError=kill -9 %p -cp /Users/tsuyoshi/SOURCE/zookeeper/bin/../build/classes:/Users/tsuyoshi/SOURCE/zookeeper/bin/../build/lib/*.jar:/Users/tsuyoshi/SOURCE/zookeeper/bin/../lib/*.jar:/Users/tsuyoshi/SOURCE/zookeeper/bin/../zookeeper-*.jar:/Users/tsuyoshi/SOURCE/zookeeper/bin/../src/java/lib/*.jar:/Users/tsuyoshi/SOURCE/zookeeper/bin/../conf: -Xmx1000m -Dcom.sun.management.jmxremote -Dcom.sun.management.jmxremote.local.only=false org.apache.zookeeper.server.quorum.QuorumPeerMain /Users/tsuyoshi/SOURCE/zookeeper/bin/../conf/zoo.cfg
```

続いてzookeeperのライブラリをインストールする必要があります。src/cの下にソースコードがあるのでこれをコンパイルします。
```
$ cd zookeeper-3.4.9/src/c
$ ./configure 
$ make
$ sudo make install
$ export LD_LIBRARY_PATH=/usr/local/lib/         # 必要に応じて
```

以上で今回のプログラムを動かすことができます。

# TODO
- sample1.ccはうまくうごかないかも

# 参考URL
- [libzookeeper Documentation(PDF)](https://media.readthedocs.org/pdf/libzookeeper/latest/libzookeeper.pdf)
- [ZooKeeper Programmer's Guide](https://zookeeper.apache.org/doc/r3.4.9/zookeeperProgrammers.html)
