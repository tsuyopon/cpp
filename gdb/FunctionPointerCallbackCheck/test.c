// $ gcc -g test.c 
#include <stdio.h>

typedef int (*FUNCPTR)(int a,int b);

int multiple(int a,int b)
{
    return(a*b);
}

int divide(int a,int b)
{
    return(a/b);
}

void main()
{
    int a,b;
    int result;
    FUNCPTR tFuncPtr;

    a=8;
    b=4;

    tFuncPtr=&multiple;
    result=(tFuncPtr)(a,b);
    printf("Answer is %d\n",result);

    tFuncPtr=&divide;
    result=(tFuncPtr)(a,b);
    printf("Answer is %d\n",result);
}
