#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

/*!
 * @brief     sample
 * @param[in] str 任意の文字列
 * @return    0:success/-1:failure
 */
static int
sample_func(char *str)
{
    int length = 0;
    char *cp = NULL;
    char *bp = NULL;

    length = strlen(str);
    if(length < 0){
        printf("Error: strlen() %s\n", strerror(errno));
        return(-1);
    }

    /* メモリ領域の確保 */
    cp = (char *)sbrk(length + 1);
    if(cp == NULL){
        printf("Error: sbrk() %s\n", strerror(errno));
        return(-1);
    }

    /* メモリ確保の確認 */
    strcpy(cp, str);
    printf("%s\n", cp);

    /* メモリ解放 */
    bp = brk(cp);
    if(bp == NULL){
        printf("Error: brk() %s\n", strerror(errno));
        return(-1);
    }

    return(0);
}

int
main(int argc, char *argv[])
{
    int rc = 0;

    if(argc != 2){
        fprintf(stderr, "Usage: %s <str>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    rc = sample_func(argv[1]);
    if(rc != 0) exit(EXIT_FAILURE);

    exit(EXIT_SUCCESS);
}
