all: hello main

hello: hello.c
	gcc -shared hello.c -o hello.so

main: main.c
	gcc main.c -o main

clean:
	rm -f main hello.so
