all: server client

.PHONY: server client

FLAGS = -g -O0
INC = -I/opt/openssl-1.1.1/include
LIB = -L/opt/openssl-1.1.1/lib -lssl -lcrypto

server:
	gcc $(FLAGS) $(INC) $(LIB) server.c -o server

client:
	gcc $(FLAGS) $(INC) $(LIB) client_SSL.c -o clientSSL

clean:
	rm -f a.out server clientSSL
