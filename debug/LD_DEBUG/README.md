LD_DEBUG環境変数でデバッグする
====

# 概要・設定

LD_DEBUG環境変数を使うと動的リンカに関連するデバッグ情報を出力できます。
とりあえず自分の方ではまだ深追いせずにただ出力させてみたのを整理しただけのメモ

サンプル用のプログラムをビルドします。
```
$ gcc test.c
```

LD_DEBUGという環境変数を使うと現在実行しているコマンドのデバッグ情報を出力してくれます。
以下はLD_DEBUGに指定できる値一覧です。
```
$ LD_DEBUG=help ls
Valid options for the LD_DEBUG environment variable are:

  libs        display library search paths
  reloc       display relocation processing
  files       display progress for input file
  symbols     display symbol table processing
  bindings    display information about symbol binding
  versions    display version dependencies
  scopes      display scope information
  all         all previous options combined
  statistics  display relocation statistics
  unused      determined unused DSOs
  help        display this help message and exit

To direct the debugging output into a file instead of standard output
a filename can be specified using the LD_DEBUG_OUTPUT environment variable.
```

以下では各々の出力を確認します。複数指定する場合にはカンマ区切りで指定できます

## libs
```
$ export LD_DEBUG=libs
$ ./a.out 
      3751:	find library=libstdc++.so.6 [0]; searching
      3751:	 search cache=/etc/ld.so.cache
      3751:	  trying file=/lib64/libstdc++.so.6
      3751:	
      3751:	find library=libm.so.6 [0]; searching
      3751:	 search cache=/etc/ld.so.cache
      3751:	  trying file=/lib64/libm.so.6
      3751:	
      3751:	find library=libgcc_s.so.1 [0]; searching
      3751:	 search cache=/etc/ld.so.cache
      3751:	  trying file=/lib64/libgcc_s.so.1
      3751:	
      3751:	find library=libc.so.6 [0]; searching
      3751:	 search cache=/etc/ld.so.cache
      3751:	  trying file=/lib64/libc.so.6
      3751:	
      3751:	
      3751:	calling init: /lib64/ld-linux-x86-64.so.2
      3751:	
      3751:	
      3751:	calling init: /lib64/libc.so.6
      3751:	
      3751:	
      3751:	calling init: /lib64/libgcc_s.so.1
      3751:	
      3751:	
      3751:	calling init: /lib64/libm.so.6
      3751:	
      3751:	
      3751:	calling init: /lib64/libstdc++.so.6
      3751:	
      3751:	
      3751:	calling init: /usr/lib64/libSegFault.so
      3751:	
      3751:	
      3751:	initialize program: ./a.out
      3751:	
      3751:	
      3751:	transferring control: ./a.out
      3751:	
sub1
      3751:	
      3751:	calling fini: ./a.out [0]
      3751:	
      3751:	
      3751:	calling fini: /usr/lib64/libSegFault.so [0]
      3751:	
      3751:	
      3751:	calling fini: /lib64/libstdc++.so.6 [0]
      3751:	
      3751:	
      3751:	calling fini: /lib64/libm.so.6 [0]
      3751:	
      3751:	
      3751:	calling fini: /lib64/libgcc_s.so.1 [0]
      3751:	
```


## reloc
```
$ export LD_DEBUG=reloc
$ ./a.out 
      3771:	
      3771:	relocation processing: /lib64/libc.so.6
      3771:	
      3771:	relocation processing: /lib64/libgcc_s.so.1 (lazy)
      3771:	
      3771:	relocation processing: /lib64/libm.so.6 (lazy)
      3771:	
      3771:	relocation processing: /lib64/libstdc++.so.6 (lazy)
      3771:	
      3771:	relocation processing: /usr/lib64/libSegFault.so (lazy)
      3771:	
      3771:	relocation processing: ./a.out (lazy)
      3771:	
      3771:	relocation processing: /lib64/ld-linux-x86-64.so.2
      3771:	
      3771:	calling init: /lib64/ld-linux-x86-64.so.2
      3771:	
      3771:	
      3771:	calling init: /lib64/libc.so.6
      3771:	
      3771:	
      3771:	calling init: /lib64/libgcc_s.so.1
      3771:	
      3771:	
      3771:	calling init: /lib64/libm.so.6
      3771:	
      3771:	
      3771:	calling init: /lib64/libstdc++.so.6
      3771:	
      3771:	
      3771:	calling init: /usr/lib64/libSegFault.so
      3771:	
      3771:	
      3771:	initialize program: ./a.out
      3771:	
      3771:	
      3771:	transferring control: ./a.out
      3771:	
sub1
      3771:	
      3771:	calling fini: ./a.out [0]
      3771:	
      3771:	
      3771:	calling fini: /usr/lib64/libSegFault.so [0]
      3771:	
      3771:	
      3771:	calling fini: /lib64/libstdc++.so.6 [0]
      3771:	
      3771:	
      3771:	calling fini: /lib64/libm.so.6 [0]
      3771:	
      3771:	
      3771:	calling fini: /lib64/libgcc_s.so.1 [0]
      3771:	
```


## files
```
$ export LD_DEBUG=files
$ ./a.out 
      3752:	
      3752:	file=/usr/lib64/libSegFault.so [0];  needed by ./a.out [0]
      3752:	file=/usr/lib64/libSegFault.so [0];  generating link map
      3752:	  dynamic: 0x00007fafcfea0da8  base: 0x00007fafcfc9d000   size: 0x00000000002040b8
      3752:	    entry: 0x00007fafcfc9dd00  phdr: 0x00007fafcfc9d040  phnum:                  9
      3752:	
      3752:	
      3752:	file=libstdc++.so.6 [0];  needed by ./a.out [0]
      3752:	file=libstdc++.so.6 [0];  generating link map
      3752:	  dynamic: 0x0000003d618eb238  base: 0x0000000000000000   size: 0x00000000003024e0
      3752:	    entry: 0x0000003d6165bb50  phdr: 0x0000003d61600040  phnum:                  8
      3752:	
      3752:	
      3752:	file=libm.so.6 [0];  needed by ./a.out [0]
      3752:	file=libm.so.6 [0];  generating link map
      3752:	  dynamic: 0x0000003d558f9ca8  base: 0x0000000000000000   size: 0x00000000002fa118
      3752:	    entry: 0x0000003d556055f0  phdr: 0x0000003d55600040  phnum:                  9
      3752:	
      3752:	
      3752:	file=libgcc_s.so.1 [0];  needed by ./a.out [0]
      3752:	file=libgcc_s.so.1 [0];  generating link map
      3752:	  dynamic: 0x0000003d59414778  base: 0x0000000000000000   size: 0x0000000000214db8
      3752:	    entry: 0x0000003d592029d0  phdr: 0x0000003d59200040  phnum:                  6
      3752:	
      3752:	
      3752:	file=libc.so.6 [0];  needed by ./a.out [0]
      3752:	file=libc.so.6 [0];  generating link map
      3752:	  dynamic: 0x0000003d549afb40  base: 0x0000000000000000   size: 0x00000000003b6498
      3752:	    entry: 0x0000003d54621840  phdr: 0x0000003d54600040  phnum:                 10
      3752:	
      3752:	
      3752:	calling init: /lib64/ld-linux-x86-64.so.2
      3752:	
      3752:	
      3752:	calling init: /lib64/libc.so.6
      3752:	
      3752:	
      3752:	calling init: /lib64/libgcc_s.so.1
      3752:	
      3752:	
      3752:	calling init: /lib64/libm.so.6
      3752:	
      3752:	
      3752:	calling init: /lib64/libstdc++.so.6
      3752:	
      3752:	
      3752:	calling init: /usr/lib64/libSegFault.so
      3752:	
      3752:	
      3752:	initialize program: ./a.out
      3752:	
      3752:	
      3752:	transferring control: ./a.out
      3752:	
sub1
      3752:	
      3752:	calling fini: ./a.out [0]
      3752:	
      3752:	
      3752:	calling fini: /usr/lib64/libSegFault.so [0]
      3752:	
      3752:	
      3752:	calling fini: /lib64/libstdc++.so.6 [0]
      3752:	
      3752:	
      3752:	calling fini: /lib64/libm.so.6 [0]
      3752:	
      3752:	
      3752:	calling fini: /lib64/libgcc_s.so.1 [0]
      3752:	
```


## symbols
```
$ export LD_DEBUG=symbols
$ ./a.out
	(省略)
      3759:	calling fini: /lib64/libm.so.6 [0]
      3759:	
      3759:	symbol=__cxa_finalize;  lookup in file=./a.out [0]
      3759:	symbol=__cxa_finalize;  lookup in file=/usr/lib64/libSegFault.so [0]
      3759:	symbol=__cxa_finalize;  lookup in file=/lib64/libstdc++.so.6 [0]
      3759:	symbol=__cxa_finalize;  lookup in file=/lib64/libm.so.6 [0]
      3759:	symbol=__cxa_finalize;  lookup in file=/lib64/libgcc_s.so.1 [0]
      3759:	symbol=__cxa_finalize;  lookup in file=/lib64/libc.so.6 [0]
      3759:	
      3759:	calling fini: /lib64/libgcc_s.so.1 [0]
      3759:	
      3759:	symbol=__cxa_finalize;  lookup in file=./a.out [0]
      3759:	symbol=__cxa_finalize;  lookup in file=/usr/lib64/libSegFault.so [0]
      3759:	symbol=__cxa_finalize;  lookup in file=/lib64/libstdc++.so.6 [0]
      3759:	symbol=__cxa_finalize;  lookup in file=/lib64/libm.so.6 [0]
      3759:	symbol=__cxa_finalize;  lookup in file=/lib64/libgcc_s.so.1 [0]
      3759:	symbol=__cxa_finalize;  lookup in file=/lib64/libc.so.6 [0]
```


## bindings
非常に長い情報がつらつらと表示される。
```
$ export LD_DEBUG=bindings
$ ./a.out 
      3845:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `_res' [GLIBC_2.2.5]
      3845:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `_IO_file_close' [GLIBC_2.2.5]
      3845:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `stderr' [GLIBC_2.2.5]
      3845:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `error_one_per_line' [GLIBC_2.2.5]
      3845:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `__malloc_initialize_hook' [GLIBC_2.2.5]
      3845:	binding file /lib64/libc.so.6 [0] to /lib64/ld-linux-x86-64.so.2 [0]: normal symbol `_dl_starting_up' [GLIBC_PRIVATE]
      3845:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `__morecore' [GLIBC_2.2.5]
      3845:	binding file /lib64/libc.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `__key_encryptsession_pk_LOCAL' [GLIBC_2.2.5]
     (以下、省略)

```


## versions
```
$ export LD_DEBUG=versions
$ ./a.out 
      3833:	checking for version `GLIBC_2.2.5' in file /lib64/libc.so.6 [0] required by file ./a.out [0]
      3833:	checking for version `GLIBC_2.3' in file /lib64/libc.so.6 [0] required by file /usr/lib64/libSegFault.so [0]
      3833:	checking for version `GLIBC_2.3.3' in file /lib64/libc.so.6 [0] required by file /usr/lib64/libSegFault.so [0]
      3833:	checking for version `GLIBC_PRIVATE' in file /lib64/libc.so.6 [0] required by file /usr/lib64/libSegFault.so [0]
      3833:	checking for version `GLIBC_2.2.5' in file /lib64/libc.so.6 [0] required by file /usr/lib64/libSegFault.so [0]
      3833:	checking for version `GLIBC_2.2.5' in file /lib64/libm.so.6 [0] required by file /lib64/libstdc++.so.6 [0]
      3833:	checking for version `GLIBC_2.3' in file /lib64/ld-linux-x86-64.so.2 [0] required by file /lib64/libstdc++.so.6 [0]
      3833:	checking for version `GCC_4.2.0' in file /lib64/libgcc_s.so.1 [0] required by file /lib64/libstdc++.so.6 [0]
      3833:	checking for version `GCC_3.3' in file /lib64/libgcc_s.so.1 [0] required by file /lib64/libstdc++.so.6 [0]
      3833:	checking for version `GCC_3.0' in file /lib64/libgcc_s.so.1 [0] required by file /lib64/libstdc++.so.6 [0]
      3833:	checking for version `GLIBC_2.14' in file /lib64/libc.so.6 [0] required by file /lib64/libstdc++.so.6 [0]
      (以下、省略)
```


## scopes
```
$ export LD_DEBUG=scopes
$ ./a.out 
      3770:	
      3770:	Initial object scopes
      3770:	object=./a.out [0]
      3770:	 scope 0: ./a.out /usr/lib64/libSegFault.so /lib64/libstdc++.so.6 /lib64/libm.so.6 /lib64/libgcc_s.so.1 /lib64/libc.so.6 /lib64/ld-linux-x86-64.so.2
      3770:	
      3770:	object=linux-vdso.so.1 [0]
      3770:	 scope 0: ./a.out /usr/lib64/libSegFault.so /lib64/libstdc++.so.6 /lib64/libm.so.6 /lib64/libgcc_s.so.1 /lib64/libc.so.6 /lib64/ld-linux-x86-64.so.2
      3770:	 scope 1: linux-vdso.so.1
      3770:	
      3770:	object=/usr/lib64/libSegFault.so [0]
      3770:	 scope 0: ./a.out /usr/lib64/libSegFault.so /lib64/libstdc++.so.6 /lib64/libm.so.6 /lib64/libgcc_s.so.1 /lib64/libc.so.6 /lib64/ld-linux-x86-64.so.2
      3770:	
      3770:	object=/lib64/libstdc++.so.6 [0]
      3770:	 scope 0: ./a.out /usr/lib64/libSegFault.so /lib64/libstdc++.so.6 /lib64/libm.so.6 /lib64/libgcc_s.so.1 /lib64/libc.so.6 /lib64/ld-linux-x86-64.so.2
      3770:	
      3770:	object=/lib64/libm.so.6 [0]
      3770:	 scope 0: ./a.out /usr/lib64/libSegFault.so /lib64/libstdc++.so.6 /lib64/libm.so.6 /lib64/libgcc_s.so.1 /lib64/libc.so.6 /lib64/ld-linux-x86-64.so.2
      3770:	
      3770:	object=/lib64/libgcc_s.so.1 [0]
      3770:	 scope 0: ./a.out /usr/lib64/libSegFault.so /lib64/libstdc++.so.6 /lib64/libm.so.6 /lib64/libgcc_s.so.1 /lib64/libc.so.6 /lib64/ld-linux-x86-64.so.2
      3770:	
      3770:	object=/lib64/libc.so.6 [0]
      3770:	 scope 0: ./a.out /usr/lib64/libSegFault.so /lib64/libstdc++.so.6 /lib64/libm.so.6 /lib64/libgcc_s.so.1 /lib64/libc.so.6 /lib64/ld-linux-x86-64.so.2
      3770:	
      3770:	object=/lib64/ld-linux-x86-64.so.2 [0]
      3770:	 no scope
      3770:	
sub1
```



## all
```
$ export LD_DEBUG=all
$ ./a.out 
	  (省略)
      3824:	symbol=_ZNSt14error_categoryD2Ev;  lookup in file=/lib64/libstdc++.so.6 [0]
      3824:	binding file /lib64/libstdc++.so.6 [0] to /lib64/libstdc++.so.6 [0]: normal symbol `_ZNSt14error_categoryD2Ev' [GLIBCXX_3.4.15]
      3824:	
      3824:	calling fini: /lib64/libm.so.6 [0]
      3824:	
      3824:	symbol=__cxa_finalize;  lookup in file=./a.out [0]
      3824:	symbol=__cxa_finalize;  lookup in file=/usr/lib64/libSegFault.so [0]
      3824:	symbol=__cxa_finalize;  lookup in file=/lib64/libstdc++.so.6 [0]
      3824:	symbol=__cxa_finalize;  lookup in file=/lib64/libm.so.6 [0]
      3824:	symbol=__cxa_finalize;  lookup in file=/lib64/libgcc_s.so.1 [0]
      3824:	symbol=__cxa_finalize;  lookup in file=/lib64/libc.so.6 [0]
      3824:	binding file /lib64/libm.so.6 [0] to /lib64/libc.so.6 [0]: normal symbol `__cxa_finalize' [GLIBC_2.2.5]
      3824:	
      3824:	calling fini: /lib64/libgcc_s.so.1 [0]
      3824:	
      3824:	symbol=__cxa_finalize;  lookup in file=./a.out [0]
      3824:	symbol=__cxa_finalize;  lookup in file=/usr/lib64/libSegFault.so [0]
      3824:	symbol=__cxa_finalize;  lookup in file=/lib64/libstdc++.so.6 [0]
      3824:	symbol=__cxa_finalize;  lookup in file=/lib64/libm.so.6 [0]
      3824:	symbol=__cxa_finalize;  lookup in file=/lib64/libgcc_s.so.1 [0]
      3824:	symbol=__cxa_finalize;  lookup in file=/lib64/libc.so.6 [0]
      3824:	binding file /lib64/libgcc_s.so.1 [0] to /lib64/libc.so.6 [0]: normal symbol `__cxa_finalize' [GLIBC_2.2.5]
```


## statistics
```
$ export LD_DEBUG=statistics
$ ./a.out 
      3734:	
      3734:	runtime linker statistics:
      3734:	  total startup time in dynamic loader: 1828577 clock cycles
      3734:		    time needed for relocation: 809667 clock cycles (44.2%)
      3734:	                 number of relocations: 1231
      3734:	      number of relocations from cache: 998
      3734:	        number of relative relocations: 4
      3734:		   time needed to load objects: 775450 clock cycles (42.4%)
sub1
      3734:	
      3734:	runtime linker statistics:
      3734:	           final number of relocations: 1248
      3734:	final number of relocations from cache: 998
```

## unused
determined unused DSOs ?
```
$ export LD_DEBUG=unused
$ ./a.out 
sub1
```

