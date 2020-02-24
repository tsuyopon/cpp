
all: normal-compile version_script-compile check

normal-compile:
	gcc -g -c -fPIC -Wall vis_comm.c vis_f1.c vis_f2.c
	gcc -g -shared -o vis-normal.so vis_comm.o vis_f1.o vis_f2.o

version_script-compile:
	gcc -g -c -fPIC -Wall vis_comm.c vis_f1.c vis_f2.c
	gcc -g -shared -o vis-vs.so vis_comm.o vis_f1.o vis_f2.o \
	    -Wl,--version-script,vis.map

check:
	readelf --syms --use-dynamic vis-normal.so | grep vis_
	readelf --syms --use-dynamic vis-vs.so | grep vis_

clean:
	rm -f *.so *.o
