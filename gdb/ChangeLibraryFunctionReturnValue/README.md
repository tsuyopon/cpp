# 概要
ChangeMyFunctionReturnValueにて独自で定義したauthenticate()関数をやめて判定をmain()のif文の中に直接strcmpを記述してしまった。  
このstrcmpの戻り値を変更したい。ただし、strcmpは独自関数ではないのでどうすれば値を変更できるのかわからない。といった場合のパターン
テストプログラムはtest.cにあります。

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
今回はmain関数にブレークポイントを貼ります。
```
$ gdb ./a.out
(gdb) b main
Breakpoint 1 at 0x100000e6f: file test.c, line 9.
(gdb) run PASS
Starting program: /Users/tsuyoshi/git/cpp/gdb/ChangeLibraryFunctionReturnValue/a.out PASS

Breakpoint 1, main (argc=2, argv=0x7fff5fbffb48) at test.c:9
9	  int retVal = -1;
```

ここでmainはそれほど量が多くないのでdisasを実行します。  
strcmpとしてはdyld_stub_strcmpと記述されている<main+84>が該当していると思われます。  

```
(gdb) disas
Dump of assembler code for function main:
0x0000000100000e60 <main+0>:	push   %rbp
0x0000000100000e61 <main+1>:	mov    %rsp,%rbp
0x0000000100000e64 <main+4>:	sub    $0x20,%rsp
0x0000000100000e68 <main+8>:	mov    %edi,-0x4(%rbp)
0x0000000100000e6b <main+11>:	mov    %rsi,-0x10(%rbp)
0x0000000100000e6f <main+15>:	movl   $0xffffffff,-0x14(%rbp)
0x0000000100000e76 <main+22>:	cmpl   $0x2,-0x4(%rbp)
0x0000000100000e7d <main+29>:	jge    0x100000ea5 <main+69>
0x0000000100000e83 <main+35>:	lea    0xb4(%rip),%rdi        # 0x100000f3e
0x0000000100000e8a <main+42>:	mov    -0x10(%rbp),%rax
0x0000000100000e8e <main+46>:	mov    (%rax),%rsi
0x0000000100000e91 <main+49>:	mov    $0x0,%al
0x0000000100000e93 <main+51>:	callq  0x100000f02 <dyld_stub_printf>
0x0000000100000e98 <main+56>:	mov    $0xfffffffe,%edi
0x0000000100000e9d <main+61>:	mov    %eax,-0x18(%rbp)
0x0000000100000ea0 <main+64>:	callq  0x100000efc <dyld_stub_exit>
0x0000000100000ea5 <main+69>:	mov    -0x10(%rbp),%rax
0x0000000100000ea9 <main+73>:	mov    0x8(%rax),%rdi
0x0000000100000ead <main+77>:	lea    0xa3(%rip),%rsi        # 0x100000f57
0x0000000100000eb4 <main+84>:	callq  0x100000f08 <dyld_stub_strcmp>
0x0000000100000eb9 <main+89>:	cmp    $0x0,%eax
0x0000000100000ebe <main+94>:	jne    0x100000eda <main+122>
0x0000000100000ec4 <main+100>:	lea    0x91(%rip),%rdi        # 0x100000f5c
0x0000000100000ecb <main+107>:	mov    $0x0,%al
0x0000000100000ecd <main+109>:	callq  0x100000f02 <dyld_stub_printf>
0x0000000100000ed2 <main+114>:	mov    %eax,-0x1c(%rbp)
0x0000000100000ed5 <main+117>:	jmpq   0x100000ef3 <main+147>
0x0000000100000eda <main+122>:	lea    0xa3(%rip),%rdi        # 0x100000f84
0x0000000100000ee1 <main+129>:	mov    $0x0,%al
0x0000000100000ee3 <main+131>:	callq  0x100000f02 <dyld_stub_printf>
0x0000000100000ee8 <main+136>:	mov    -0x14(%rbp),%edi
0x0000000100000eeb <main+139>:	mov    %eax,-0x20(%rbp)
0x0000000100000eee <main+142>:	callq  0x100000efc <dyld_stub_exit>
0x0000000100000ef3 <main+147>:	xor    %eax,%eax
0x0000000100000ef5 <main+149>:	add    $0x20,%rsp
0x0000000100000ef9 <main+153>:	pop    %rbp
0x0000000100000efa <main+154>:	retq   
End of assembler dump.
Current language:  auto; currently minimal
```

strcmp関数を実行したその直後にcmp命令があるのでここでif文判定していると考えられるのでcmp実行直前の<main+89>にブレークポイントを設定します。
```
(gdb) b *main+89
Breakpoint 2 at 0x100000eb9: file test.c, line 18.
(gdb) c
Continuing.

Breakpoint 2, 0x0000000100000eb9 in main (argc=2, argv=0x7fff5fbffb48) at test.c:18
18	  if( strcmp(argv[1], "PASS") == 0)
```

ここの$raxを0に変更すれば成功、0以外に設定すれば失敗となります。  
今回はPASSからFAILに変更するために1にでも設定しましょう。
```
(gdb) info r $rax
rax            0x0	0
(gdb) set $rax=1
(gdb) info r $rax
rax            0x1	1
(gdb) c
Continuing.
Wrong Input, exiting...

Program exited with code 0377.
```
これでstrcmpのような関数も置き換えられることができました。

