all: client tlsclient
client:
	g++ -o client client.cc

tlsclient:
	g++ -lssl -lcrypto -lstdc++ -o tlsclient tlsclient.cc

clean:
	rm -f client tlsclient
