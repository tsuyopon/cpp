all: helloserver helloclient

helloserver:
	gcc -o helloserver helloserver.c -lzmq

helloclient:
	gcc -o helloclient helloclient.c -lzmq

clean:
	rm -f helloserver helloclient
