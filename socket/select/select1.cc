/*
 * This is select() sample program.
 *
 * <usage>
 * 1. execute program
 *   $ ./a.out
 * 2. Monitoring STDIN_FILENO by using select().
 * 3. Insert "Enter" From Keyboard
 *  
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static void
noop(int signo)
{
    return;
}

#define BUFSIZE 1024

int
main(int argc, char **argv)
{
    char *buf[BUFSIZE];
    struct sigaction act;

    act.sa_handler = noop;
    sigemptyset(&act.sa_mask);
#ifdef SA_RESTART
    act.sa_flags = SA_RESTART;
#endif
    if (sigaction(SIGINT, &act, NULL) < 0) {  
        fputs("sigaction errror\n", stderr);
        exit(3);
    }

    for (;;) {
        int retval;
        fd_set readset;       // Recv select() data.
        struct timeval time;  // timeout

		// See. http://intuniv.cs.shinshu-u.ac.jp/Lecture/NetProg/chapter5/fdset.html
        FD_ZERO(&readset);               // CLEAR ZERO.
        FD_SET(STDIN_FILENO, &readset);
		printf("1:%d\n", readset);

        time.tv_sec = 1;   // Seconds.
        time.tv_usec = 0;  // Micro seconds.

		// select() returns file discriptor number.
        retval = select(STDIN_FILENO + 1, &readset, NULL, NULL, &time);
		printf("2:%d\n", retval);
        if (retval > 0)
            break;
        if (retval == 0) puts("timed out; retry");
        else if (retval < 0) puts("detect exception; retry");
    }
    read(STDIN_FILENO, buf, BUFSIZE);  
    puts("read ok");
    exit(EXIT_SUCCESS);
}
