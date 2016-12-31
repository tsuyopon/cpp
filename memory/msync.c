/*
 * msyncを使うとmmapに対する処理の同期が可能となる
 *
 * 以下のプログラムを呼び出すと/tmp/mmapにの1文字を取得して、その文字を１つインクリメントする。
 * ./a.outを実行するごとに文字が変わっていることが確認できる。
 * 
 * [使い方]
 *  $ cat /tmp/mmap 
 *  a
 *  $ ./a.out 
 *  a
 *  $ ./a.out 
 *  b
 *  $ ./a.out 
 *  c
 *
 * 参考: http://kotaroito.hatenablog.com/entry/2014/01/20/230346
 */
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>

int main(int argc, char* argv[])
{
    int fd;
    char *cp;

    fd = open("/tmp/mmap", O_RDWR);
    cp = mmap(NULL, sizeof(char), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    printf("%c\n", *cp);

    *cp = *cp + 1;

	// これをいれなくてもmmapを実行したプロセスが終了すると自動的にメモリが解放される(munmapが呼ばれる!?)
	// munmapが呼ばれない場合にはいつsyncされるかわからないので、明示的にそのタイミングを指示したい場合にmsyncを使う
    msync(cp, sizeof(char), 0);
	sleep(10);

    return 0;
}
