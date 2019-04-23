#include <stdio.h>

// 以下の２つの関数は共有ライブラリ以外でも使えるが参考に、明示的に呼び出されていないが動作する
void __attribute__ ((constructor)) my_init(void) {
    printf("constructor2\n");
}

void __attribute__ ((destructor)) my_fini(void) {
    printf("destructor2\n");
}

void hello(void) {
    printf("Hello2, library world.\n");
}
