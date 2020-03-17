
.PHONY: all clean

all: test test.so

test: main.o
	$(CXX) -o $@ $^ -ldl -Wl,-R,'$$ORIGIN'

so.o: so.cpp
	$(CXX) -fPIC -c -o $@ $^

test.so: so.o
	$(CXX) -shared -o $@ $^

clean:
	-rm *.o *.so test

