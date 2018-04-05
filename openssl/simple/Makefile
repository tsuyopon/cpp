all: server client

.PHONY: server client

server:
	gcc -lssl -lcrypto server.c -o server

client:
	gcc -lssl -lcrypto client.c -o client

clean:
	rm -f a.out server client
