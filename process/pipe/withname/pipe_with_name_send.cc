/*
 * SEND (OPEN FIFO FILE AND WRITE DATA INTO FIFO FILE.)
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

	// OPENING FIFO FILE
	fifo = open("fifofile", O_WRONLY);
	fgets(buffer, 256, stdin);

	// WRITE DATA
	write(fifo, buffer, strlen(buffer)+1);
	close(fifo);

	return 0;
}
