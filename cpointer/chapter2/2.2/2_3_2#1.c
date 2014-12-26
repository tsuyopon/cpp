#include<stdio.h>
#include<stdlib.h>

int main(){
	int *pi = (int*)malloc(sizeof(int));
	*pi = 5;
	free(pi);

	// うっかり誤って既に解放されているものを２重解放してしまった場合には実行エラーとなります。
	free(pi);
}
