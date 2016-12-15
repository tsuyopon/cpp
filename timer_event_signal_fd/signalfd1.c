/*
 * see http://codezine.jp/article/detail/4803
 */
#include <sys/signalfd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int  signal_fd( );
void timer_set( );

int main( ) {

    struct signalfd_siginfo si;

    int fd = signal_fd( );
    timer_set( );

    while( 1 ) {
	read( fd, &si, sizeof( struct signalfd_siginfo ));

	if( si.ssi_signo == SIGINT )
	    printf("Got SIGINT" );
	else if( si.ssi_signo == SIGQUIT )
	    printf("Got SIGQUIT" );
	else
	    printf( "Read unexpected signal" );

	if( si.ssi_code == SI_USER )
	    printf( " by USER ... perhaps kill command.\n" );
	else if( si.ssi_code == SI_KERNEL )
	    printf( " by KERNEL ... perhaps terminal.\n" );
	else if( si.ssi_code == SI_TIMER )
	    printf( " by TIMEUP.\n" );
	else
	    printf( " ssi_code:unexpected code : %d\n", si.ssi_code );
    }
    return 0;
}

int  signal_fd( ) {
    sigset_t mask;

    sigemptyset( &mask );
    sigaddset( &mask, SIGINT );
    sigaddset( &mask, SIGQUIT );
    sigprocmask( SIG_BLOCK, &mask, 0 );
    return signalfd( -1, &mask, 0 );
}

void timer_set( ) {
    struct sigevent ev;
    ev.sigev_notify = SIGEV_SIGNAL;
    ev.sigev_signo  = SIGINT;

    struct itimerspec ts;
    ts.it_value.tv_sec = 4;
    ts.it_value.tv_nsec = 0;
    ts.it_interval.tv_sec = 4;
    ts.it_interval.tv_nsec = 0;

    timer_t timer_id;
    timer_create( CLOCK_MONOTONIC,&ev, &timer_id );
    timer_settime( timer_id, 0, &ts, 0 );
}
