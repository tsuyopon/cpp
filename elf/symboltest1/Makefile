all:
	gcc -c values_sub.c
	gcc values.c values_sub.o -o values
	nm values_sub.o
	-echo
	-echo
	nm values

clean:
	rm -f values_sub.o values
