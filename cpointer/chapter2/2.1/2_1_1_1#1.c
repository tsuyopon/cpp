#include<stdio.h>
#include<stdlib.h>

int main(){

	// 1度目のメモリ割当を行っています。
	int *pi = (int*)(sizeof(int));
	*pi = 5;

	// 2度目のメモリ割当をpiアドレスに行っていますが、事前にfreeをしていないのでこのような場合にはSegmentation Faultとなります。
	pi = (int*)malloc(sizeof(int));
}
