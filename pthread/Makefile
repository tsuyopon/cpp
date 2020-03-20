all: hellothread hellomutex hellodeadlock threadlocal

LIB = -lpthread
hellothread: hellothread.cc
	g++ $^ -o $@.out $(LIB)

hellomutex: hellomutex.cc
	g++ $^ -o $@.out $(LIB)

hellodeadlock: hellodeadlock.cc
	g++ $^ -o $@.out $(LIB)

threadlocal: threadlocal.cc
	g++ $^ -o $@.out $(LIB)

clean:
	rm -f *.out
