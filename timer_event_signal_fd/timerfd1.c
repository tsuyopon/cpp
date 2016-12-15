/*
 *
 * see http://codezine.jp/article/detail/4799
 */
#include <sys/timerfd.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define TV2SEC(tv) ((double)((tv).tv_sec) + (double)((tv).tv_usec / 1000000.0))
int main(int argc, char ** argv ) {

    struct timespec cur;
    struct timeval  tv1,tv2;

    if( argc < 4 ) {
	fprintf( stderr, "Usage: %s <num> <num> <num>...\n", argv[0] );
	exit( EXIT_FAILURE );
    }

    int fd = timerfd_create( CLOCK_MONOTONIC, 0 );
    clock_gettime( CLOCK_MONOTONIC, &cur );

    struct itimerspec val;
    val.it_value.tv_sec     = cur.tv_sec + atoi( argv[1] );
    val.it_value.tv_nsec    = 0;
    val.it_interval.tv_sec  = atoi( argv[2] );
    val.it_interval.tv_nsec = 0;
    timerfd_settime( fd, TFD_TIMER_ABSTIME, &val, 0 );
    gettimeofday( &tv1, 0 );

    uint64_t read_cnt;
    int      cnt;
    for( cnt = 0; cnt < atoi( argv[3] ); cnt ++ ) {
	read( fd, &read_cnt, sizeof( uint64_t ));
	gettimeofday( &tv2, 0 );
	double rtn = TV2SEC( tv2 ) - TV2SEC( tv1 );
	printf( "timerfd %d Path... [%f]\n", cnt + 1, rtn );
	tv1 = tv2;
    }
    close( fd );
    exit( EXIT_SUCCESS );
}
