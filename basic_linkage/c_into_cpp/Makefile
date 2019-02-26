programs := main

.PHONY: all
all: $(programs)

$(programs): libhello.a

libhello.a: libhello.a(hello.o) 

hello.o: hello.h

.PHONY: clean
clean:
	$(RM) *.o *.a $(programs)
