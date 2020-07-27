// エスケープシーケンスでカラー表示させるだけのサンプル
// 参考: https://qiita.com/PruneMazui/items/8a023347772620025ad6
#include<stdio.h>
#include<math.h>

int main(){

	int i, j, hex;

	// 文字色
	printf("### CHARACTER COLOR\n");
	for (i = 30; i <= 37; i++){
		printf("\e[%dm%d\e[m ", i, i);
	}

	// 背景色
	printf("\n\n### BACKGROUND COLOR\n");
	for (i = 40; i <= 47; i++){
		printf("\e[%dm%d\e[m ", i, i);
	}

	// 文字色（拡張）
	printf("\n\n### CHARACTOR COLOR(Extension)\n");
	for (i = 0; i < 16; i++){
		for (j = 0; j < 16; j++){
			hex=((i*16 + j));
			printf("\e[38;5;%dm0x%02X\e[m ", hex, hex);
		}
	}

	// 背景色（拡張）
	printf("\n\n### BACKGROUND COLOR(Extension)\n");
	for (i = 0; i < 16; i++){
		for (j = 0; j < 16; j++){
			hex=((i*16 + j));
			printf("\e[48;5;%dm0x%02X\e[m ", hex, hex);
		}
	}
	printf("\n");

}
