/*
 * __attribute__((cleanup(func))) によるデストラクタサンプル
 */
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

static inline void ctor(int32_t *p, size_t sz, ...) {
    va_list ap;
    va_start(ap, sz);
    for (size_t idx=0; idx<sz; ++idx) {
        p[idx] = va_arg(ap, int32_t);
    }
    va_end(ap);
}

static inline void dtor(void *p) {
    free(*(void **)p);
    puts("freed!");
}

#define CTOR_HEAP_ARRY(var, sz, ...) \
__attribute__((cleanup(dtor))) int32_t *var = (int32_t *)malloc(sizeof(int32_t)*sz); \
ctor(var, sz, __VA_ARGS__)

#define ARRY_SZ (5)

int main() {
    CTOR_HEAP_ARRY(p_arry, ARRY_SZ, 1, 2, 3, 4, 5);
    for (size_t idx=0; idx<ARRY_SZ; ++idx) {
        printf("p_arry[%zu]=%" PRId32 "\n", idx, p_arry[idx]);
    }
}
