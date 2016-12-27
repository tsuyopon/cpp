all: hello main

hello: hello.c
	gcc -shared hello.c -o hello.so -fPIC

# export-dynamicが存在しないとプログラム実行した際にmainhoge()がundefined symbolと表示されます
main: main.c
	gcc -export-dynamic main.c -o main -ldl

clean:
	rm -f main hello.so
