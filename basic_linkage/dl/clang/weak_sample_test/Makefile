all: hello hello2 main

hello: hello.c
	gcc -g -shared hello.c  -o hello.so -fPIC

hello2: hello2.c
	gcc -g -shared hello2.c -o hello2.so -fPIC -Wl,-Bsymbolic

main: hello hello2 main.c
	gcc -g -export-dynamic main.c -o main -ldl

clean:
	rm -f main hello.so hello2.so
