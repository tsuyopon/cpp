#include<stdio.h>

int main(){
	int num;
	int *pi = &num;
	printf("Value of pi: %p\n", pi);

	// voidへのポインタはどのようなデータ型でもさすことができます
	void* pv = pi;
	pi = (int*)pv;
	printf("Value of pi: %p\n", pi);
}
