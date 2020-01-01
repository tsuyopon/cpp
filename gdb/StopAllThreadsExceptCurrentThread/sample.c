// [compile]
//     $ gcc sample.c -lpthread -g
#include <stdio.h>
#include <pthread.h>

void* thread_main( void* args )
{
    int i;
    fprintf( stderr, "start thread\n" );
    for( i=0; i<100; ++i ){
        printf("this is loop %d/100\n", i);
        sleep(1);
    }
    fprintf( stderr, "end thread\n" );
    return NULL;
}

int main()
{
    int i;
    char command[256];

    fprintf( stderr, "start\n");

    for( i=0; i<5; ++i ){

        pthread_t thread;
        pthread_create( &thread, NULL, thread_main, (void *)NULL );

    }

    // スレッドが即時終了しないように意図的に配置している(本当はpthread_joinが良い)
    getchar();

    fprintf( stderr, "end mainthread\n" );

    return 0;
}
