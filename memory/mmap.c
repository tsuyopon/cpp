/*
 * mmapを使ったメモリ割り当てを行う
 *  mmapはユーザー空間からカーネル空間にコピーする処理が存在しないのでfopen等と比較しても超高速らしい
 *
 * REFERENCE: http://linuxjm.sourceforge.jp/html/LDP_man-pages/man2/mmap.2.html
 */
// http://funini.com/kei/mmap/mmap_api.shtml
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
    char *addr;
    int fd;
    struct stat sb;
    off_t offset, pa_offset;
    size_t length;
    ssize_t s;

    if (argc < 3 || argc > 4) {
        fprintf(stderr, "%s file offset [length]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1)           /* called fstat to obtain file size */
        handle_error("fstat");

    offset = atoi(argv[2]);
    pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);  // sysconf(_SC_PAGE_SIZE) == getpagesize()
        /* offset for mmap() must be page aligned */

    // オフセットの位置がファイルサイズを超過していたらエラー
    if (offset >= sb.st_size) {         // st_size means file size.
        fprintf(stderr, "offset is past end of file\n");
        exit(EXIT_FAILURE);
    }

    // length引数が指定された場合と指定されなかった場合で取得するlengthを決定する
    if (argc == 4) {
        length = atoi(argv[3]);
        if (offset + length > sb.st_size)
            length = sb.st_size - offset;
                /* Can't display bytes past end of file */

    } else {    /* No length arg ==> display to end of file */
        length = sb.st_size - offset;
    }

    addr = mmap(NULL, length + offset - pa_offset, PROT_READ, MAP_PRIVATE, fd, pa_offset);
    if (addr == MAP_FAILED)
        handle_error("mmap");

    s = write(STDOUT_FILENO, addr + offset - pa_offset, length);
    if (s != length) {
        if (s == -1)
            handle_error("write");

        fprintf(stderr, "partial write");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
