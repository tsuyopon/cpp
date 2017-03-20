#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static void *hello(void *vptr_args) {
    fputs("Hello World\n", stderr);
    return NULL;
}

int main(void) {
    int i;
    pthread_t thread;

    if (pthread_create(&thread, NULL, hello, NULL) != 0) {
        return EXIT_FAILURE;
    }

    sleep(60);

    if (pthread_join(thread, NULL) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

