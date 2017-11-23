# 概要
templateを使ったブレークポイントの貼り方

# 詳細
予め次のコマンドでデバッグビルドを行っておくこと
```
$ g++ -g3 -O0 test.cc
```

### 

ブレークポイントを貼ってみる以下ではFoo<T>のTとしてintである場合にブレークポイントを貼ってみることにする。  
「T Foo<T>::bar(T)」の場合にはブレークポイントを貼る時に戻り値の型を指定しないことに注意すること
```
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/cpp/gdb/TemplateBreakpint/a.out...done.
(gdb) b Foo<int>::bar(int)
Breakpoint 1 at 0x40096b: file test.cc, line 16.
(gdb) run
Starting program: /home/tsuyoshi/cpp/gdb/TemplateBreakpint/./a.out 

Breakpoint 1, Foo<int>::bar (this=0x7fffffffe31f, c=10) at test.cc:16
16	        return c * 2;
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64 libgcc-4.8.5-16.el7.x86_64 libstdc++-4.8.5-16.el7.x86_64
(gdb) where
#0  Foo<int>::bar (this=0x7fffffffe31f, c=10) at test.cc:16
#1  0x00000000004008ad in main (argc=1, argv=0x7fffffffe408) at test.cc:24
(gdb) list
11	{
12	public:
13	
14	    T bar(T c)
15	    {
16	        return c * 2;
17	    }
18	};
19	
20	int main(int argc, char** argv)
(gdb) bt
#0  Foo<int>::bar (this=0x7fffffffe31f, c=10) at test.cc:16
#1  0x00000000004008ad in main (argc=1, argv=0x7fffffffe408) at test.cc:24
(gdb) c
Continuing.
20
200
201
[Inferior 1 (process 14174) exited normally]
```

今度はTがfloat側の方にブレークポイントを張ってみる。
```
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/cpp/gdb/TemplateBreakpint/a.out...done.
(gdb) b Foo<float>::bar(float)
Breakpoint 1 at 0x4009a9: file test.cc, line 16.
(gdb) run
Starting program: /home/tsuyoshi/cpp/gdb/TemplateBreakpint/./a.out 
20

Breakpoint 1, Foo<float>::bar (this=0x7fffffffe31e, c=100) at test.cc:16
16	        return c * 2;
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64 libgcc-4.8.5-16.el7.x86_64 libstdc++-4.8.5-16.el7.x86_64
(gdb) where
#0  Foo<float>::bar (this=0x7fffffffe31e, c=100) at test.cc:16
#1  0x00000000004008c8 in main (argc=1, argv=0x7fffffffe408) at test.cc:28
(gdb) c
Continuing.
200

Breakpoint 1, Foo<float>::bar (this=0x7fffffffe31d, c=100.5) at test.cc:16
16	        return c * 2;
(gdb) where
#0  Foo<float>::bar (this=0x7fffffffe31d, c=100.5) at test.cc:16
#1  0x00000000004008f1 in main (argc=1, argv=0x7fffffffe408) at test.cc:32
(gdb) c
Continuing.
201
[Inferior 1 (process 14180) exited normally]
```


今度はcoinにブレークポイントを貼ってみる。
この場合には先程と異なり、ブレークポイントを貼る際に戻り値の型も指定しないと認識してくれない。先程のbarは戻り値自体がTだったので不要ということか?(TODO: ちょっとよくわかっていない)
```
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/cpp/gdb/TemplateBreakpint/a.out...done.
(gdb) b coin<int>(int)
Function "coin<int>(int)" not defined.
Make breakpoint pending on future shared library load? (y or [n]) n
(gdb) b void coin<int>(int)
Breakpoint 1 at 0x40097d: file test.cc, line 6.
(gdb) run
Starting program: /home/tsuyoshi/cpp/gdb/TemplateBreakpint/./a.out 

Breakpoint 1, coin<int> (v=20) at test.cc:6
6	    std::cout << v << std::endl;
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64 libgcc-4.8.5-16.el7.x86_64 libstdc++-4.8.5-16.el7.x86_64
(gdb) bt
#0  coin<int> (v=20) at test.cc:6
#1  0x00000000004008b4 in main (argc=1, argv=0x7fffffffe408) at test.cc:24
(gdb) c
Continuing.
20
200
201
[Inferior 1 (process 14188) exited normally]
```

# 参考URL
- https://stackoverflow.com/questions/1666963/debugging-templates-with-gdb
