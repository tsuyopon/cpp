all: server 

.PHONY: server

FLAGS = -g -O0
INC = -I/opt/openssl-1.1.1/include
LIB = -L/opt/openssl-1.1.1/lib -lssl -lcrypto

server:
	gcc $(FLAGS) $(INC) $(LIB) server.c -o server

clean:
	rm -f a.out server
