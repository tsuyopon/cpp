all: hello main

hello: hello.c
	gcc -shared hello.c -o hello.so -fPIC

main: main.c
	gcc main.c -o main -ldl

clean:
	rm -f main hello.so
