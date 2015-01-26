/*
 * key入力 + Enterがあるまでスレッド処理を実行するプログラムです。
 * もっとも簡単なスレッド処理を実現しているプログラムです。
 */
#include <stdio.h>
#include <unistd.h>  // sleep()
#include <pthread.h>

// pthread_createにて指定されているハンドラ
void* thread( void* args )
{	
    int counter = 0;
    while(1){
        printf( "thread : %d\n", counter );
        sleep(1);
        counter++;
    }

    return NULL;
}

// メインスレッド
int main() 
{
    pthread_t th;

    // スレッド作成と起動
    pthread_create( &th, NULL, thread, (void *)NULL );

    // "キー入力 + Enter" があるまで停止する
    getchar();

    return 0;
}
