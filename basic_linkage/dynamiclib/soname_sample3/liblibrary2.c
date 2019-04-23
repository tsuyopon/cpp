#include <stdio.h>
#include "libhello.h"
#include "liblibrary2.h"

// 以下の２つの関数は共有ライブラリ以外でも使えるが参考に、明示的に呼び出されていないが動作する
void __attribute__ ((constructor)) my_init(void) {
    printf("liblibrary2 constructor\n");
}

void __attribute__ ((destructor)) my_fini(void) {
    printf("liblibrary2 destructor\n");
}

void liblibrary2(void) {
    printf("liblibrary2\n");
    hello();
}
