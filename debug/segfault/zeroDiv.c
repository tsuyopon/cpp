#include <stdio.h>

foo(a){return a / 0;}

main(){
        printf("%d\n", foo(5));
}
