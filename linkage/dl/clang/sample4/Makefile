all: hello main

hello: hello.c
	gcc -shared hello.c  -o hello.so -fPIC

hello2: hello2.c
	gcc -shared hello2.c -o hello2.so -fPIC

main1: hello hello2 main.c
	gcc -export-dynamic main.c -o main -ldl

main2: hello hello2 main.c
	gcc -DRTLDGLOBAL -export-dynamic main.c -o main -ldl

clean:
	rm -f main hello.so hello2.so
