# 概要
たとえば、SIGPIPEを受け取るプログラムだと必ずブレークしてしまいます。(たとえ、それが指定したスレッド番号であっても)
こうれがなにかの操作で発生するとデバッグに非常に煩わしい出力となります。
```
(gdb) b Continuation::handleEvent if ( ($_thread != 2) && ($_thread != 4) )
Breakpoint 1 at 0x51ce05: file /home/tsuyoshi/trafficserver/iocore/eventsystem/I_Continuation.h, line 153.
(gdb) c
Continuing.

Program received signal SIGPIPE, Broken pipe.
[Switching to Thread 0x7f42450ff700 (LWP 14497)]
0x00007f424789d6ad in write () from /lib64/libpthread.so.0
```

次のコマンドを実行するとSIGPIPEを無視します。
```
(gdb)  handle SIGPIPE nostop
Signal        Stop	Print	Pass to program	Description
SIGPIPE       No	Yes	Yes		Broken pipe
(gdb) c
Continuing.
```

これによって他のスレッドもデバッグできるようになります。
```
Breakpoint 1, Continuation::handleEvent (this=0x1f628a0, event=1, data=0x1f74ca0) at /home/tsuyoshi/trafficserver/iocore/eventsystem/I_Continuation.h:153
153	/home/tsuyoshi/trafficserver/iocore/eventsystem/I_Continuation.h: そのようなファイルやディレクトリはありません.
(gdb) thread
[Current thread is 5 (Thread 0x7f423f26e700 (LWP 14510))]
```

# 参考URL
- https://stackoverflow.com/questions/18935446/program-received-signal-sigpipe-broken-pipe
