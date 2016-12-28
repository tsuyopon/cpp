all: simple_get simple_get2 multi_get
	
simple_get:
	g++ -o simple_get -lcurl -I/usr/include/curl simple_get.cc

simple_get2:
	g++ -o simple_get2 -lcurl -I/usr/include/curl simple_get2.cc

multi_get:
	g++ -o multi_get -lcurl -I/usr/include/curl multi_get.cc

clean: 
	rm -f simple_get simple_get2 multi_get test.txt
