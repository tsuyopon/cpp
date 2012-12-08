/*
 * RECV (CREATE FIFO FILE AND RECV DATA FROM FIFO FILE)
 *
 * See Below URL For Reference.
 *     http://www.geocities.jp/sugachan1973/doc/funto45.html
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	int fifo;
	char buffer[256];

	// CREATING FIFO FILE
	mkfifo("fifofile", 0777);

	// OPENING FIFO FILE
	fifo = open("fifofile", O_RDONLY);

	// RECV DATA
	read(fifo, buffer, 256);
	printf("Message: %s", buffer);

	// CLOSE
	close(fifo);
}
