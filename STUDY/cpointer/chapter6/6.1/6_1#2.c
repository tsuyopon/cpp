#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _person {
	char* firstName;
	char* lastName;
	char* title;
	unsigned int age;
} Person;

int main(){

	/*
	 * アロー演算子でのアクセス
	 */

	// インスタンス宣言と構造体領域確保
	Person *ptrPerson;
	ptrPerson = (Person*)malloc(sizeof(Person));

	// age以外の変数についてはアドレス宣言しかしていないので、アドレス宣言した変数には実体メモリの割当が必要となります。
	ptrPerson->firstName = (char*)malloc(strlen("Emily")+1);

	// 値の設定
	strcpy(ptrPerson->firstName, "Emily");
	ptrPerson->age = 23;

	// 出力
	printf("arrow: firstName=%s, age=%d\n", ptrPerson->firstName, ptrPerson->age);

	/*
	 * ドット演算子でのアクセス
	 */

	// インスタンス宣言と構造体領域確保
	Person *ptrPerson2;
	ptrPerson2 = (Person*)malloc(sizeof(Person));
	(*ptrPerson2).firstName = (char*)malloc(strlen("Emily")+1);

	// 値の設定と出力
	strcpy((*ptrPerson2).firstName, "Emily");
	(*ptrPerson2).age = 23;
	printf("dot:   firstName=%s, age=%d\n", ptrPerson2->firstName, ptrPerson2->age);

}
