all: heap mmap

heap:
	gcc -o useheap -DUSEHEAP malloctest.c

mmap:
	gcc -o usemmap ./malloctest.c

clean:
	rm -f useheap usemmap a.out
