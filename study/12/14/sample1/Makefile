sample-dbg: sample-dbg.o
	g++ -o $@ sample-dbg.o

sample: sample.o
	g++ -o $@ sample.o

sample-dbg.o: sample1.cc
	g++ -o $@ -c sample1.cc

sample.o: sample1.cc
	g++ -o $@ -c -DNDEBUG sample1.cc

clean:
	rm -f sample.o sample-dbg.o sample sample-dbg
