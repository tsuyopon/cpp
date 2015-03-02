/*
 * 2つのmutexを用いてデッドロックが起こるプログラムです。
 * あくまでもデッドロックが起こるサンプルなので実際にこのように実装することはよくありません
 *
 * http://www.hakodate-ct.ac.jp/~tokai/tokai/research/drill/thread.html
 *   3. デッドロック参照
 */
#include <stdio.h>
#include <unistd.h>  // sleep()
#include <pthread.h>

pthread_mutex_t mutex1;  // Mutex
pthread_mutex_t mutex2;  // Mutex

// スレッド1
void* thread1( void* args )
{
    // mutex1 を取得してブロック
    pthread_mutex_lock( &mutex1 );
    printf( "スレッド１が mutex1 を取得しました\n" );

    sleep( 1 );
    printf( "スレッド１が mutex2 の開放を待ってます\n" );

    // 他のスレッドが mutex2 を返却するのを待つ
    // mutex2 が返却されたら mutex2 を取得してブロック
    pthread_mutex_lock( &mutex2 );
    printf( "スレッド１が mutex2 を取得しました\n" );

    // ここからクリティカルセクション

    printf( "スレッド１ 実行中\n" );
    sleep( 2 );

    // ここまでクリティカルセクション

    // mutex2 開放
    pthread_mutex_unlock( &mutex2 );
    printf( "スレッド１が mutex2 を開放しました\n" );

    // mutex1 開放
    pthread_mutex_unlock( &mutex1 );
    printf( "スレッド１が mutex1 を開放しました\n" );

    printf( "スレッド1 終了\n" );

    return NULL;
}


// スレッド2
void* thread2( void* args )
{
    // mutex2 を取得してブロック
    pthread_mutex_lock( &mutex2 );
    printf( "スレッド2が mutex2 を取得しました\n" );

    sleep( 1 );
    printf( "スレッド2が mutex1 の開放を待ってます\n" );

    // 他のスレッドが mutex1 を返却するのを待つ
    // mutex1 が返却されたら mutex1 を取得してブロック
    pthread_mutex_lock( &mutex1 );
    printf( "スレッド2が mutex1 を取得しました\n" );

    // ここからクリティカルセクション

    printf( "スレッド2 実行中\n" );
    sleep( 2 );

    // ここまでクリティカルセクション

    // mutex1 開放
    pthread_mutex_unlock( &mutex1 );
    printf( "スレッド2が mutex1 を開放しました\n" );

    // mutex2 開放
    pthread_mutex_unlock( &mutex2 );
    printf( "スレッド2が mutex2 を開放しました\n" );

    printf( "スレッド2 終了\n" );

    return NULL;
}


// メインスレッド
int main() 
{
    pthread_t th1, th2;
	
    // mutex1,2 作成
    pthread_mutex_init( &mutex1, NULL );
    pthread_mutex_init( &mutex2, NULL );
	
    // スレッド1,2の作成と起動
    pthread_create( &th1, NULL, thread1, (void *)NULL );
    pthread_create( &th2, NULL, thread2, (void *)NULL );
	
    // スレッド終了を待つ
    pthread_join( th1, NULL );
    pthread_join( th2, NULL );
	
    // mutex 開放
    pthread_mutex_destroy( &mutex1 );
    pthread_mutex_destroy( &mutex2 );
	
    return 0;
}
