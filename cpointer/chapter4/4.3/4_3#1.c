#include<stdio.h>
#include<stdlib.h>

int main(){
	int *pv = (int*)malloc(5*sizeof(int));
	int i;

	for(i=0; i < 5 ; i++){
		pv[i] = i+1;
		// ポインタ記法で記述すると以下となります。
		// *(pv+i) = i+1;
	}

}
