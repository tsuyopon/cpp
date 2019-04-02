#include <stdio.h>

__attribute__((constructor))
static void constructor() {
    puts("constructor");
}

__attribute__((destructor))
static void destructor() {
    puts("destructor");
}

int main(int argc, char const* argv[])
{
    puts("call main");
    return 0;
}
