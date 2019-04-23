# -staticをつけると出来上がるバイナリがstaticリンクとなります。
all: clean dynamiclib
	gcc -Wall -g -c sample.c -o sample.o
	gcc -v -g -o sample sample.o -L. -l:liblibrary.so.1.0 -l:liblibrary.so.2.0 -Wl,-rpath -Wl,./
	@echo "#########################################################"
	@echo "###### use \"make execute\" target to execute sample library #####"
	@echo "#########################################################"

# LD_LIBRARY_PATHが指定されているのに注意する
execute: 
	LD_LIBRARY_PATH="." ./sample

# 「「ldconfig -n .」でlibhello.so.0やlibhello.so.1が生成されます
dynamiclib:
	gcc -fPIC -Wall -g -c libhello1.c
	gcc -g -shared -Wl,-soname,libhello.so.1 -o libhello.so.1.0 libhello1.o -lc -I.
	/sbin/ldconfig -n .
	gcc -fPIC -Wall -g -c libhello2.c
	gcc -g -shared -Wl,-soname,libhello.so.2 -o libhello.so.2.0 libhello2.o -lc -I.
	/sbin/ldconfig -n .
	gcc -fPIC -Wall -g -c liblibrary1.c
	gcc -g -shared -Wl,-soname,liblibrary.so.1 -o liblibrary.so.1.0 liblibrary1.o -lc -L. -l:libhello.so.1.0 -I.
	/sbin/ldconfig -n .
	gcc -fPIC -Wall -g -c liblibrary2.c
	gcc -g -shared -Wl,-soname,liblibrary.so.2 -o liblibrary.so.2.0 liblibrary2.o -lc -L. -l:libhello.so.2.0 -I.
	/sbin/ldconfig -n .

clean:
	rm -f *.o lib*.so* sample
