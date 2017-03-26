all: clean hello hellopthread

hello:
		g++ -g -std=c++11 -pthread hello.cc -o hello
		g++ -std=c++11 -pthread hellomany.cc -o hellomany

hellopthread:
		gcc -g -lpthread hellopthread.c -o hellopthread

clean:
	rm -f hello hellopthread

