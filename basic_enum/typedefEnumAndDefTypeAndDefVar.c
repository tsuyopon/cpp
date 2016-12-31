#include<stdio.h>

// "enum Etype{E1,E2}"を別名Eとして定義している。
// "enum{E1,E2}"の型はEtypeという名称となる。
typedef enum Etype{E1,E2} E;   // typedef enum Etype {E1,E2} E;　でもOK(Etypeの後にスペースをあけること)

int main(){

		// typedefで宣言した場合にはEは変数ではなく型なので、変数定義がひつようとなる。
		E a1;
		a1 = E1;

		// 2つめの定義も可能となる。
		E a2;
		a2 = E2;

		// Etypeとして型宣言して利用することも可能
		enum Etype a3;
		enum Etype a4;
		a3 = E1;
		a4 = E2;

		printf("a1 value=%d, a2 value=%d, a3 value=%d, a4 value=%d\n", a1, a2, a3, a4);
		return 0;
}
