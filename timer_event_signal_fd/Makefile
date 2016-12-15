eventfd1:
	gcc -o $@ $@.c

timerfd1:
	gcc -o $@ $@.c -lrt

signalfd1:
	gcc -o $@ $@.c -lrt

clean:
	rm -f ./a.out eventfd1 timerfd1 signalfd1
