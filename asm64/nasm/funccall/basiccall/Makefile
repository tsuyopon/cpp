main: main.o func.obj
	gcc -g -o main main.o func.obj

clean:
	rm -f *.o *.obj *.bin main a.out

%.o: %.c %.h
	gcc -c $*.c $*.h

%.obj: %.asm
	nasm -f elf64 -o $*.obj $*.asm
	
