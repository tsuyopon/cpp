/*
 * 構造体の宣言とアクセス方法について
 */
#include<stdio.h>
#include<stdlib.h>

typedef struct _person {
	char* firstName;
	char* lastName;
	char* title;
	unsigned int age;
} Person;

// 以下のようにtypedefでない場合には宣言時に"struct _person person[n];"としなければならない
/*
struct _person {
	char* firstName;
	char* lastName;
	char* title;
	unsigned int age;
};
*/

int main(){

	// 構造体サイズ領域をあらかじめ確保
	Person person[1];
	person[0].firstName = "first";        // アクセスにはドットを使う
	printf("%s\n", person[0].firstName);

	// 構造体サイズ領域を動的に取得する
	Person *dyPerson;
	dyPerson = (Person*)malloc(sizeof(Person));
	dyPerson->firstName = "second";      // アクセスにはアロー演算子を使う
	printf("%s\n", dyPerson->firstName);

}
