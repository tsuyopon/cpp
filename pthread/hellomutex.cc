/*
 * スレッドにおける排他制御機構であるMutexのもっとも簡単なサンプル 
 * http://www.hakodate-ct.ac.jp/~tokai/tokai/research/drill/thread.html
 */
#include <stdio.h>
#include <unistd.h>  // usleep()
#include <pthread.h>

pthread_mutex_t mutex;  // Mutex

// スレッド1
void* thread1( void* args )
{
    // 他のスレッドが mutex を返却するを待つ
    // mutex が返却されたら mutex を取得してブロック
    pthread_mutex_lock( &mutex );
	
    // ここからクリティカルセクション

    int i = 0;
    for( i=0; i < 10; ++i){
        printf( "thread1 - %d\n", i );
        usleep( 1000 );  // スレッドを 1000 マイクロ秒停止
    }
	
    // ここまでクリティカルセクション

    // mutex返却
    pthread_mutex_unlock( &mutex );

    return NULL;
}


// スレッド2
void* thread2( void* args )
{
    // 他のスレッドが mutex を返却するを待つ
    // mutex が返却されたら mutex を取得してブロック
    pthread_mutex_lock( &mutex );
	
    // ここからクリティカルセクション

    int i = 0;
    for( i=0; i < 10; ++i){
        printf( "thread2 - %d\n", i );
        usleep( 2000 );  // スレッドを 2000 マイクロ秒停止
    }
	
    // ここまでクリティカルセクション

    // mutex返却
    pthread_mutex_unlock( &mutex );

    return NULL;
}


// メインスレッド
int main() 
{
    pthread_t th1, th2;
	
    // mutex 作成
    pthread_mutex_init( &mutex, NULL );
	
    // スレッド1,2の作成と起動
    pthread_create( &th1, NULL, thread1, (void *)NULL );
    pthread_create( &th2, NULL, thread2, (void *)NULL );
	
    // スレッド終了を待つ
    pthread_join( th1, NULL );
    pthread_join( th2, NULL );
	
    // mutex 開放
    pthread_mutex_destroy( &mutex );
	
    return 0;
}

