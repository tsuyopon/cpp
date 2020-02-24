# -staticをつけると出来上がるバイナリがstaticリンクとなります。
all: clean dynamiclib
	gcc -Wall -g -c sample.c -o sample.o
	gcc -v -g -o sample sample.o -L. -lhello -Wl,--enable-new-dtags -Wl,-rpath,'$$ORIGIN'
	#gcc -v -g -o sample sample.o -L. -lhello -Wl,-rpath,'$$ORIGIN' 
	@echo "#########################################################"
	@echo "###### use \"make execute\" target to execute sample library #####"
	@echo "#########################################################"

# LD_LIBRARY_PATHが指定されているのに注意する
execute: 
	./sample

# 「「ldconfig -n .」でlibhello.so.0が生成されます
dynamiclib:
	gcc -fPIC -Wall -g -c libhello.c
	gcc -g -shared -Wl,-soname,libhello.so.0 -o libhello.so.0.0 libhello.o -lc
	/sbin/ldconfig -n .
	ln -sf libhello.so.0 libhello.so

clean:
	rm -f *.o libhello.so* sample
