# 概要
独自で定義したauthenticate()関数の戻り値をgdbを使って変更する。  
テストプログラムはtest.cにあります。

今回のパターンは実はretValを変更すれば一撃なのですが、
もし、test.cのmain()内の判定方法が以下のようになった場合にも適用できるようなTIPSとなります。
```
if(authenticate(argv[1]) == 0)
```

# 詳細

### gdb用にコンパイルする
デバッグ情報を付与するために-gを付与します。またgcc最適化しないように-O0オプションも付与します。
コンパイルしたら引数を与えてプログラムの動作を確認してみます。
```
$ gcc -g -O0 test.c 
$ ./a.out FAIL
 Wrong Input, exiting...
$ ./a.out PASS
  Authenticated ...program continuing...
```

### gdbを実行し、ブレークポイントを貼っておく
あらかじめgdbを実行してから戻り値を変更したい関数authenticate()にブレークポイントを設定します。
```
$ gdb ./a.out
(gdb) b authenticate
Breakpoint 1 at 0x100000e1c: file test.c, line 12.
```

### FAILで起動し、PASSに変更する
つまり本来であれば認証失敗なのですが、これを通過させるようにすることができます。
設定したブレークポイントauthenticate()で止まったら、main()からauthenticate()に処理を進めていきたいのでstep実行します。

```
(gdb) run FAIL
Starting program: /Users/tsuyoshi/git/cpp/gdb/ChangeMyFunctionReturnValue/a.out FAIL

Breakpoint 1, authenticate (test=0x7fff5fbffcce "FAIL") at test.c:12
12	  if(strcmp(test,"PASS") == 0 ) {
(gdb) step
15	      return 1; /* fail */
```

この時点でreturn 1に処理を写しましたが、$raxを見てみます。  
$raxには関数の戻り値が入っています。
```
(gdb) info r $rax
rax            0xfffffffffffffff6	-10
```

どうやらこの時点ではreturn 1が設定されていないようなので、閉じ括弧}まで処理を進めるためにもう一度stepして$raxを確認します。
```
(gdb) step
17	}
(gdb) info r $rax
rax            0xfffffffffffffff6	-10
```

この時点でも進んでいないようです。
ここからアセンブラ命令を１つ進める(stepiを実行)するとreturnで設定した値に変化します。
```
(gdb) stepi
0x0000000100000e4d	17	}
(gdb) info r $rax
rax            0x1	1
```

$raxの値が閉じ括弧の処理が終わってやっと変化しました。どうやらこの$raxレジスタを0に変更すればPASSとして扱われそうです。
```
(gdb) set $rax=0
(gdb) info r $rax
rax            0x0	0
(gdb) c
Continuing.
Authenticated ...program continuing...

Program exited normally.
```
このようにして偽装することができます。

### PASSで起動し、FAILに変更する
authenticate()にブレークポイントを貼った状態でPASSを引数に与えて実行します
```
(gdb) run PASS
Starting program: /Users/tsuyoshi/git/cpp/gdb/ChangeMyFunctionReturnValue/a.out PASS

Breakpoint 1, authenticate (test=0x7fff5fbffcce "PASS") at test.c:12
12	  if(strcmp(test,"PASS") == 0 ) {
```

authenticateのブレークポイント到達時だと$raxが初期化されていなさそうです。
return0にstep実行されると$raxは0に初期化されているようです。
```
(gdb) info r $rax
rax            0x7fff5fbffb58	140734799805272
(gdb) step
13		  return 0; /* success*/
(gdb) info r $rax
rax            0x0	0
```

では、ここで$raxに1をセットすればよさそうかと思いセットしてみます。(先ほどは}の後stepiした直後にセットしています)
```
(gdb) step
17	}
(gdb) set $rax=1
(gdb) info r $rax
rax            0x1	1
```

上記で変更されるように見えますが、なんとstepiを実行すると$raxが0に戻ってしまいます。  
推測するにおそらく先ほどのrax=0は初期化されて設定されただけで、returnの値は}が終わった後stepi実行した際に呼ばれるものと思われます。

```
(gdb) stepi
0x0000000100000e4d	17	}
(gdb) info r $rax
rax            0x0	0
(gdb) c
Continuing.
Authenticated ...program continuing...
```

なのでstepi実行した後にset $rax=1と変更すると「return 1;」したのと同様の操作ができます。


### returnを利用する

run PASSすると「Authenticated〜」と表示されます
```
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/cpp/gdb/ChangeMyFunctionReturnValue/a.out...done.
(gdb) run PASS
Starting program: /home/tsuyoshi/cpp/gdb/ChangeMyFunctionReturnValue/./a.out PASS
Authenticated ...program continuing...
[Inferior 1 (process 19919) exited with code 047]
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64
```

run PASSしてauthenticate関数で即座に0を返してみることができます。この場合は「Authenticated〜」となります。
```
(gdb) b authenticate
Breakpoint 1 at 0x400619: file test.c, line 12.
(gdb) c
The program is not being run.
(gdb) run PASS
Starting program: /home/tsuyoshi/cpp/gdb/ChangeMyFunctionReturnValue/./a.out PASS

Breakpoint 1, authenticate (test=0x7fffffffe674 "PASS") at test.c:12
12	  if(strcmp(test,"PASS") == 0 ) {
(gdb) return 0
Make authenticate return now? (y or n) y
#0  0x000000000040068e in main (argc=2, argv=0x7fffffffe3e8) at test.c:29
29	  retVal = authenticate(argv[1]);
(gdb) c
Continuing.
Authenticated ...program continuing...
[Inferior 1 (process 19945) exited with code 047]
```

続いて、run PASSしてauthenticate関数で即座に1を返してみることにします。この場合は「Wrong Input, exiting...」と書き換えることができました。
```
(gdb) run PASS
Starting program: /home/tsuyoshi/cpp/gdb/ChangeMyFunctionReturnValue/./a.out PASS

Breakpoint 1, authenticate (test=0x7fffffffe674 "PASS") at test.c:12
12	  if(strcmp(test,"PASS") == 0 ) {
(gdb) return 1
Make authenticate return now? (y or n) y
#0  0x000000000040068e in main (argc=2, argv=0x7fffffffe3e8) at test.c:29
29	  retVal = authenticate(argv[1]);
(gdb) c
Continuing.
Wrong Input, exiting...
[Inferior 1 (process 19957) exited with code 01]
```

関数の戻り値はreturnを使うと簡単に制御できるようです。

- 参考
  - https://rat.cis.k.hosei.ac.jp/article/devel/debugongccgdb2.html

# 参考URL
- Modify-function-return-value Hack! — Part 1
 - http://opensourceforu.efytimes.com/2011/08/modify-function-return-value-hack-part-1/

