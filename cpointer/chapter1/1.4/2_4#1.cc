#include<stdio.h>

int main(){

	// 定数宣言
	const int limit = 500;

	// 定数への定数ポインタの宣言
	const int * const cpci = &limit;

	// 定数への定数ポインタへのポインタ宣言
	const int * const * pcpci;
	pcpci = &cpci;

	// 「**pcpci」により「*cpci」と同じ値を指し示すようになります。
	printf("cpci_value=%d, pcpci_value=%d\n", *cpci, **pcpci);

}
