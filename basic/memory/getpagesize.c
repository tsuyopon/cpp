#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

/*!
 * @brief     ページサイズを取得する
 * @return    0:success/-1:failure
 */
static int
get_memory_pagesize(void)
{
    int psize = 0;

    psize = getpagesize();
    if(psize < 0){
        printf("Error: getpagesize() %s\n", strerror(errno));
        return(-1);
    }

    return(psize);
}

int
main(int argc, char *argv[])
{
    int rc = 0;

    if(argc != 1){
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // getpagesizeはシステムのメモリ管理におけるページサイズを取得します。 
    // Cライブラリ関数のsysconf(_SC_PAGESIZE)を利用しても、同様の情報を取得できます。 
    // OS毎にこの値はことなります
    rc = get_memory_pagesize();
    if(rc < 0) exit(EXIT_FAILURE);

    printf("pagesize = %d(byte/page)\n", rc);

    exit(EXIT_SUCCESS);
}
