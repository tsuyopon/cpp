main1: clean hello1 main
main2: clean hello2 main

clean:
	rm -f main hello.so

hello1: hello.c
	gcc -DSETHOGE -shared hello.c -o hello.so -fPIC

hello2: hello.c
	gcc -shared hello.c -o hello.so -fPIC

main:
	gcc -export-dynamic main.c -o main -ldl

