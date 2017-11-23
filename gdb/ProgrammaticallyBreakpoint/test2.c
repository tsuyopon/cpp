#include <stdio.h>
#include <signal.h>

void main(int argc, char** argv)
{
    printf("before\n");
    raise(SIGINT);
    printf("after\n");
}
