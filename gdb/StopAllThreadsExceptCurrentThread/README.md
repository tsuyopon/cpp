# 概要
マルチスレッドプログラムにおいて、全てのスレッドを停止して、特定のスレッドだけデバッグ実行させたい場合の方法について

# コンパイル
```
$ gcc sample.c -lpthread -g
```

# 詳細
通常はマルチスレッドプログラムでgdbを操作していると"Switching to Thread"という表示が出てきて、他のスレッドに稼働状態が定期的に移行してしまいます。
```
(gdb) b thread_main
Breakpoint 1 at 0x4006c9: file sample.c, line 9.
(gdb) run
Starting program: /home/tsuyoshi/git/cpp/gdb/StopAllThreadsExceptCurrentThread/./a.out 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".
start
[New Thread 0x7ffff77f1700 (LWP 4007)]
[Switching to Thread 0x7ffff77f1700 (LWP 4007)]

Breakpoint 1, thread_main (args=0x0) at sample.c:9
9	    fprintf( stderr, "start thread\n" );
Missing separate debuginfos, use: debuginfo-install glibc-2.17-260.el7_6.6.x86_64
(gdb) info thread
[New Thread 0x7ffff6ff0700 (LWP 4008)]
  Id   Target Id         Frame 
  3    Thread 0x7ffff6ff0700 (LWP 4008) "a.out" 0x00007ffff78efff1 in clone () from /lib64/libc.so.6
* 2    Thread 0x7ffff77f1700 (LWP 4007) "a.out" thread_main (args=0x0) at sample.c:9
  1    Thread 0x7ffff7fef740 (LWP 4003) "a.out" 0x00007ffff78efff1 in clone () from /lib64/libc.so.6
(gdb) n
start thread
[Switching to Thread 0x7ffff6ff0700 (LWP 4008)]

Breakpoint 1, thread_main (args=0x0) at sample.c:9
9	    fprintf( stderr, "start thread\n" );
(gdb) 
start thread
[New Thread 0x7ffff67ef700 (LWP 4009)]
10	    for( i=0; i<100; ++i ){
(gdb) 
11	        printf("this is loop %d/100\n", i);
(gdb) info thread
[New Thread 0x7ffff5fee700 (LWP 4010)]
  Id   Target Id         Frame 
  5    Thread 0x7ffff5fee700 (LWP 4010) "a.out" 0x00007ffff78efff1 in clone () from /lib64/libc.so.6
  4    Thread 0x7ffff67ef700 (LWP 4009) "a.out" 0x00007ffff78efff1 in clone () from /lib64/libc.so.6
* 3    Thread 0x7ffff6ff0700 (LWP 4008) "a.out" thread_main (args=0x0) at sample.c:11
  2    Thread 0x7ffff77f1700 (LWP 4007) "a.out" thread_main (args=0x0) at sample.c:10
  1    Thread 0x7ffff7fef740 (LWP 4003) "a.out" 0x00007ffff78efff1 in clone () from /lib64/libc.so.6
(gdb) n
this is loop 0/100
12	        sleep(1);
(gdb) n
this is loop 0/100
[Switching to Thread 0x7ffff67ef700 (LWP 4009)]

Breakpoint 1, thread_main (args=0x0) at sample.c:9
9	    fprintf( stderr, "start thread\n" );
(gdb) info thread
  Id   Target Id         Frame 
  5    Thread 0x7ffff5fee700 (LWP 4010) "a.out" 0x00007ffff7bcd4bc in __lll_lock_wait_private () from /lib64/libpthread.so.0
* 4    Thread 0x7ffff67ef700 (LWP 4009) "a.out" thread_main (args=0x0) at sample.c:9
  3    Thread 0x7ffff6ff0700 (LWP 4008) "a.out" 0x00007ffff78b6fad in nanosleep () from /lib64/libc.so.6
  2    Thread 0x7ffff77f1700 (LWP 4007) "a.out" 0x00007ffff78b6fad in nanosleep () from /lib64/libc.so.6
  1    Thread 0x7ffff7fef740 (LWP 4003) "a.out" 0x00007ffff7bc5c90 in __nptl_create_event () from /lib64/libpthread.so.0	
```

info threadでスレッドが全て起動したことが確認できたら、次のset scheduler-locking onをセットして全スレッドを停止することができます。
その後、nextを実行しても"Switching to Thread"という他のスレッドへの移動表記は見当たらなくなりました。その後、info threadを実行しても稼働スレッドが変化していないことが確認できます。
```
(gdb) set scheduler-locking on
(gdb) n
start thread
10	    for( i=0; i<100; ++i ){
(gdb) 
11	        printf("this is loop %d/100\n", i);
(gdb) 
this is loop 0/100
12	        sleep(1);
(gdb) 
10	    for( i=0; i<100; ++i ){
(gdb) 
11	        printf("this is loop %d/100\n", i);
(gdb) 
this is loop 1/100
12	        sleep(1);
(gdb) 

10	    for( i=0; i<100; ++i ){
(gdb) 
11	        printf("this is loop %d/100\n", i);
(gdb) 
this is loop 2/100
12	        sleep(1);
(gdb) 
10	    for( i=0; i<100; ++i ){
(gdb) 
11	        printf("this is loop %d/100\n", i);
(gdb) 
this is loop 3/100
12	        sleep(1);
(gdb) info thread
  Id   Target Id         Frame 
  5    Thread 0x7ffff5fee700 (LWP 4010) "a.out" 0x00007ffff7bcd4bc in __lll_lock_wait_private () from /lib64/libpthread.so.0
* 4    Thread 0x7ffff67ef700 (LWP 4009) "a.out" thread_main (args=0x0) at sample.c:12
  3    Thread 0x7ffff6ff0700 (LWP 4008) "a.out" 0x00007ffff78b6fad in nanosleep () from /lib64/libc.so.6
  2    Thread 0x7ffff77f1700 (LWP 4007) "a.out" 0x00007ffff78b6fad in nanosleep () from /lib64/libc.so.6
  1    Thread 0x7ffff7fef740 (LWP 4003) "a.out" 0x00007ffff7bc5c90 in __nptl_create_event () from /lib64/libpthread.so.0
```


初期状態に戻すには次の設定を行います。これで定期的に"Switching to Thread"と他のスレッドへと稼働状態が移行することになります。
```
(gdb) set scheduler-locking on
```


