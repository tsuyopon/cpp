# -staticをつけると出来上がるバイナリがstaticリンクとなります。
all: clean dynamiclib
	gcc -Wall -g -c sample.c -o sample.o
	gcc -v -g -o sample sample.o -L. -l:libhello.so.0.0 -l:libhello.so.1.0
	@echo "#########################################################"
	@echo "###### use \"make execute\" target to execute sample library #####"
	@echo "#########################################################"

# LD_LIBRARY_PATHが指定されているのに注意する
execute: 
	LD_LIBRARY_PATH="." ./sample

# 「「ldconfig -n .」でlibhello.so.0やlibhello.so.1が生成されます
dynamiclib:
	gcc -fPIC -Wall -g -c libhello.c
	gcc -g -shared -Wl,-soname,libhello.so.0 -o libhello.so.0.0 libhello.o -lc
	/sbin/ldconfig -n .
	gcc -fPIC -Wall -g -c libhello2.c
	gcc -g -shared -Wl,-soname,libhello.so.1 -o libhello.so.1.0 libhello2.o -lc
	/sbin/ldconfig -n .

clean:
	rm -f *.o libhello.so* sample
