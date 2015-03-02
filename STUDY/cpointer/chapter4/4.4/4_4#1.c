//
// mallocで割り当てた領域が不足するので、callocで再割当を行うプログラム
//
#include<stdio.h>
#include<stdlib.h>

char* getLine(void){
	const size_t sizeIncrement = 10;
	char* buffer = malloc(sizeIncrement);

	// currentPositionの先頭はbufferと同じアドレス値を指しています。
	char* currentPosition = buffer;
	size_t maximumLength = sizeIncrement;
	size_t length = 0;
	int character;

	// malloc()で正しくメモリ割当できなければNULL
	if(currentPosition == NULL){ return NULL; }

	// \nが入力されるまでずっと文字を読み込みます。
	while(1){
		// 標準入力から1文字読み込みます。
		character = fgetc(stdin);

		// 改行が入力されたらwhile文をbreakします。
		if(character == '\n'){ break; }

		// 文字数がmaximumLengthを超えたらreallocで領域を増加します。
		if(++length >= maximumLength){

			// reallocで再割当を行います。割り当てていた文字数を超えた場合にはmaximumLengthを10追加しています。
			char *newBuffer = realloc(buffer, maximumLength += sizeIncrement);
			if(newBuffer == NULL){
				free(buffer);
				return NULL;
			}

			// currentPositionのアドレス値を算出します。
			currentPosition = newBuffer + (currentPosition - buffer);

			// 文字列先頭のアドレスはnewBufferです。
			buffer = newBuffer;
		}

		// currentPositionの値に文字列を追加しています。
		*currentPosition++ = character;
	}

	// whileが終了したので、最後の文字列に改行を追加します。
	*currentPosition = '\n';
	return buffer;
}

int main(){
	char *ret;
	ret = getLine();
	printf("%s\n", ret);
	if( ret != NULL ){
		free(ret);
	}
}
