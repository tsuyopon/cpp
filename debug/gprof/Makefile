
compile:
	g++ -pg -o gproftest gproftest.cc

execute:
	./gproftest
	gprof ./gproftest gmon.out

clean:
	rm -f gproftest gmon.out
