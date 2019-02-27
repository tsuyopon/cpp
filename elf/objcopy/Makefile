

all: build_and_objcopy

bunld_and_objcopy:
	gcc -c binary.c 
	objcopy --add-section=bindata=binary.dat --set-section-flags=bindata=contents,alloc,load,readonly,data binary.o binary_tmp.o
	gcc binary_tmp.o -o binary
	./binary

clean:
	rm -f binary binary.o  binary_tmp.o
