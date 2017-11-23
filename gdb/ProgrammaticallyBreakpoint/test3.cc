#include <stdio.h>
#include <csignal>

int main(int argc, char** argv)
{
    printf("before\n");
    std::raise(SIGINT);
    printf("after\n");
}
