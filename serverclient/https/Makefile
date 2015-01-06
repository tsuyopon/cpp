all: simple-https-client simple-https-server

simple-https-client:
	g++ simple-https-client.cc -lssl -lcrypto -L/usr/lib64 -o client

simple-https-server:
	g++ simple-https-server.cc -lssl -lcrypto -L/usr/lib64 -o server
