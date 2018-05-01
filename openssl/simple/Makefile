all: server client

.PHONY: server client

server:
	gcc -lssl -lcrypto server.c -o server

client:
	gcc -lssl -lcrypto client_BIO.c -o clientBIO
	gcc -lssl -lcrypto client_SSL.c -o clientSSL

clean:
	rm -f a.out server clientBIO clientSSL
