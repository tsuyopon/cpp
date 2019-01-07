# 概要
PLT(Procedure Linkage Table)とGOT(Global Offset Table)の仕組みを確認する。
ELFではPLTを用いて遅延リンクできるようにしている。

遅延リンクとは、共有ライブラリのロード時にシンボル解決を行うのではなく、関数が呼び出される際にシンボル解決を行う。

ちゃんとコードを読んだ訳ではないので間違っているかもしれないが概念的には次のようなイメージです。
- .text領域から.plt領域にあるアドレスをcallする
- .plt領域にあるアドレスをcallする。これは.got.plt領域を指している。
- .got.plt領域に存在する領域から該当のアドレスというのは実は.plt領域でcallq命令を実行した直後のアドレスが入っている。
- .got.pltにあるアドレスを実行すると関数実行の段階になって初めてシンボル解決をして、その関数の処理を実行してから、.plt領域の元の制御に戻す。そして、.got.pltの値として指し示していた直後のアドレスを該当の関数のアドレスへと書き換えを行う。(.pltではなく.got.pltを書き込むのはRW可能領域であるから)
- これによって、同じ関数を2度目以降も実行する場合には、.textから.plt領域にあるアドレスをcallし、.plt領域にあるアドレスをcallすと.got.plt領域を指し示す。これは先ほど参照したアドレスとは書き換わっていて本来の関数を指し示すようになっている。


test.cで使われている共有ライブラリのprintf関数を呼び出すことで、PLTの挙動を確認します。
```
$ gmake
$ ls ./a.out
```

# 詳細
Global Offset Tableを参照する。

```
$ objdump -R a.out 

a.out:     file format elf64-x86-64

DYNAMIC RELOCATION RECORDS
OFFSET           TYPE              VALUE 
0000000000600ff8 R_X86_64_GLOB_DAT  __gmon_start__
0000000000601018 R_X86_64_JUMP_SLOT  puts
0000000000601020 R_X86_64_JUMP_SLOT  __libc_start_main
0000000000601028 R_X86_64_JUMP_SLOT  __gmon_start__
```


mainの箇所だけ参照することにする。test.cのソースコードでprintfが2行あるのには訳があった。
***でputs@pltに最適化されていることがわかります。
```
$ objdump -d a.out 
...
000000000040052d <main>:
  40052d:	55                   	push   %rbp
  40052e:	48 89 e5             	mov    %rsp,%rbp
  400531:	bf e0 05 40 00       	mov    $0x4005e0,%edi
  400536:	e8 d5 fe ff ff       	callq  400410 <puts@plt>      // ***
  40053b:	bf ee 05 40 00       	mov    $0x4005ee,%edi
  400540:	e8 cb fe ff ff       	callq  400410 <puts@plt>      // ***
  400545:	b8 00 00 00 00       	mov    $0x0,%eax
  40054a:	5d                   	pop    %rbp
  40054b:	c3                   	retq   
  40054c:	0f 1f 40 00          	nopl   0x0(%rax)
...


今度は、Procedure Linkage Tableをみてみる。先ほどのcallqで400410を指し示していましたのでその箇所をみるようにします。
```
$ objdump -d -j .plt ./a.out

./a.out:     file format elf64-x86-64


Disassembly of section .plt:

0000000000400400 <puts@plt-0x10>:
  400400:	ff 35 02 0c 20 00    	pushq  0x200c02(%rip)        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  400406:	ff 25 04 0c 20 00    	jmpq   *0x200c04(%rip)        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  40040c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000400410 <puts@plt>:
  400410:	ff 25 02 0c 20 00    	jmpq   *0x200c02(%rip)        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  400416:	68 00 00 00 00       	pushq  $0x0
  40041b:	e9 e0 ff ff ff       	jmpq   400400 <_init+0x20>

0000000000400420 <__libc_start_main@plt>:
  400420:	ff 25 fa 0b 20 00    	jmpq   *0x200bfa(%rip)        # 601020 <_GLOBAL_OFFSET_TABLE_+0x20>
  400426:	68 01 00 00 00       	pushq  $0x1
  40042b:	e9 d0 ff ff ff       	jmpq   400400 <_init+0x20>

0000000000400430 <__gmon_start__@plt>:
  400430:	ff 25 f2 0b 20 00    	jmpq   *0x200bf2(%rip)        # 601028 <_GLOBAL_OFFSET_TABLE_+0x28>
  400436:	68 02 00 00 00       	pushq  $0x2
  40043b:	e9 c0 ff ff ff       	jmpq   400400 <_init+0x20>
```

ではgdbを使うことによって、callqの２つの前後での処理をみてみることにします。
まずは、callqの手前で止めます。
```
$ gdb ./a.out 
(gdb) b main
Breakpoint 1 at 0x400531: file test.c, line 5.
(gdb) run
Starting program: /home/tsuyoshi/git/cpp/basic_linkage/dl/clang/sample1/hoge/./a.out 

Breakpoint 1, main () at test.c:5
5		printf("Hello, World!\n");
Missing separate debuginfos, use: debuginfo-install glibc-2.17-260.el7.x86_64
(gdb) disas
Dump of assembler code for function main:
   0x000000000040052d <+0>:	push   %rbp
   0x000000000040052e <+1>:	mov    %rsp,%rbp
=> 0x0000000000400531 <+4>:	mov    $0x4005e0,%edi
   0x0000000000400536 <+9>:	callq  0x400410 <puts@plt>
   0x000000000040053b <+14>:	mov    $0x4005ee,%edi
   0x0000000000400540 <+19>:	callq  0x400410 <puts@plt>
   0x0000000000400545 <+24>:	mov    $0x0,%eax
   0x000000000040054a <+29>:	pop    %rbp
   0x000000000040054b <+30>:	retq   
End of assembler dump.
```

では、ここでcallqを実行する前に先ほどの0x400410が指し示していた0x601018(.got.plt)のアドレス先のアドレスがどのようになっているかを確認してみます。
0x00400416という値は最初の0x400410直後の命令であったことを最初のobjdumpの結果から確認してください。
```
(gdb) x 0x601018
0x601018 <puts@got.plt>:	0x00400416
```

では、その後進めてみます。１つめのcallqを通過すると0x601018のアドレスが0xf7a7e530へと変化しました。このアドレスがputs関数を指し示していると思われます。
```
(gdb) s
Hello, World!
6		printf("Goodbye, World!\n");
(gdb) x 0x601018
0x601018 <puts@got.plt>:	0xf7a7e530
(gdb) disas
Dump of assembler code for function main:
   0x000000000040052d <+0>:	push   %rbp
   0x000000000040052e <+1>:	mov    %rsp,%rbp
   0x0000000000400531 <+4>:	mov    $0x4005e0,%edi
   0x0000000000400536 <+9>:	callq  0x400410 <puts@plt>
=> 0x000000000040053b <+14>:	mov    $0x4005ee,%edi
   0x0000000000400540 <+19>:	callq  0x400410 <puts@plt>
   0x0000000000400545 <+24>:	mov    $0x0,%eax
   0x000000000040054a <+29>:	pop    %rbp
   0x000000000040054b <+30>:	retq   
End of assembler dump.
```

なお、2つめのcallqを通過した後には0x601018のアドレスが書き変わらないことを確認しておきます。
```
(gdb) s
Goodbye, World!
7		return 0;
(gdb) x 0x601018
0x601018 <puts@got.plt>:	0xf7a7e530
(gdb) disas
Dump of assembler code for function main:
   0x000000000040052d <+0>:	push   %rbp
   0x000000000040052e <+1>:	mov    %rsp,%rbp
   0x0000000000400531 <+4>:	mov    $0x4005e0,%edi
   0x0000000000400536 <+9>:	callq  0x400410 <puts@plt>
   0x000000000040053b <+14>:	mov    $0x4005ee,%edi
   0x0000000000400540 <+19>:	callq  0x400410 <puts@plt>
=> 0x0000000000400545 <+24>:	mov    $0x0,%eax
   0x000000000040054a <+29>:	pop    %rbp
   0x000000000040054b <+30>:	retq   
End of assembler dump.
```

以上により、GOTとPLTの仕組みをみました。


# 参考資料
- プログラムがmainにたどりつくまで(PDF)
  - PLTとGOTというスライドを参照すると良い
  - http://ukai.jp/Slides/2006/1024-gree/binhacks.pdf
