# -staticをつけると出来上がるバイナリがstaticリンクとなります。
all: clean staticlib
	gcc -Wall -g -c sample.c -o sample.o
	gcc -static -g -o sample sample.o -L. -lhello-static

staticlib:
	gcc -Wall -g -c -o libhello-static.o libhello.c
	ar rcs libhello-static.a libhello-static.o

clean:
	rm -f *.o *.a sample
