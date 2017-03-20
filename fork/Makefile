all: vfork fork

vfork:
	gcc -DVFORK -o vfork fork_vfork.c

fork:
	gcc -o fork fork_vfork.c

clean:
	rm -f vfork fork
