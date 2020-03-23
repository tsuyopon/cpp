all: hello subhello greeding main

hello: hello.c
	gcc -g3 -shared hello.c -o hello.so -fPIC -ldl

subhello: subhello.c
	gcc -g3 -shared subhello.c -o subhello.so -lsqlite3 -fPIC

greeding: greeding.c
	gcc -g3 -shared greeding.c -o greeding.so -lsqlite3 -fPIC

main: main.c
	gcc -g3 main.c -o main -ldl

clean:
	rm -f main *.so db_test.sqlite3
