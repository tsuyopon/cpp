#include<stdio.h>

inline int max(int a, int b) {
  return a > b ? a : b;
}

int main(){
	int ret;
	ret = max(3, 5);
	printf("answer is %d\n", ret);
}
