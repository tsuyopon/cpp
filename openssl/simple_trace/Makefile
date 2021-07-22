all: server client

.PHONY: server client

FLAGS = -g -O0
INC = -I/opt/openssl-1.1.1/include -I.
LIB = -L/opt/openssl-1.1.1/lib -lssl -lcrypto

server:
	gcc $(FLAGS) $(INC) $(LIB) trace.c server.c -o server

client:
	gcc $(FLAGS) $(INC) $(LIB) trace.c client_BIO.c -o clientBIO
	gcc $(FLAGS) $(INC) $(LIB) trace.c client_SSL.c -o clientSSL

clean:
	rm -f a.out server clientBIO clientSSL
	rm -rf *.dSYM
