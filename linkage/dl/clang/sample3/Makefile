all: hello main

hello1: hello.c
	gcc -shared hello.c -o hello.so -fPIC

hello2: hello.c
	gcc -Wl,-Bsymbolic -shared hello.c -o hello.so -fPIC

main1: hello1 main.c
	gcc -export-dynamic main.c -o main -ldl

main2: hello2 main.c
	gcc -export-dynamic main.c -o main -ldl

clean:
	rm -f main hello.so
