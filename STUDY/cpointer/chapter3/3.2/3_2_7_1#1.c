#include<stdio.h>
#include<stdlib.h>

// 利用者がポインタのアドレスを取り出してキャストする負担を軽減するためのマクロ
#define safeFree(p) safeFree2((void**)&(p))

// 独自のfree関数を作成する方法
void safeFree2(void **pp){

	// *ppはアドレスを表しています。
	if(pp != NULL && *pp != NULL){
		free(*pp);
		*pp = NULL;   // freeをしたらNULLをしておくのがよいでしょう。
	}
}

int main(){
	int *pi;
	pi = (int*)malloc(sizeof(int));
	*pi = 5;
	printf("Before: %p\n", pi);
	safeFree(pi);
	printf("After: %p\n",  pi);
	safeFree(pi);
	return(EXIT_SUCCESS);
}
