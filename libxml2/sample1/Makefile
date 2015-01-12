all: xpath1 xpath2 treewalk1 rssparse 

xpath1:
	g++ -lxml2 -I/usr/include/libxml2 xpath_sample1.cc -o xpath1

xpath2:
	g++ -lxml2 -I/usr/include/libxml2 xpath_sample2.cc -o xpath2

treewalk1:
	g++ -lxml2 -I/usr/include/libxml2 treewalk1.cc -o treewalk1

rssparse:
	g++ -lxml2 -I/usr/include/libxml2 rssparse.cc -o rssparse

clean:
	rm -f xpath1 xpath2 treewalk1 rssparse 
