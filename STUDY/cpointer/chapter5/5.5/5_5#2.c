/*
 * 文字列配列のsortを関数ポインタを利用して行う
 */
#include<stdio.h>

// 関数ポインタの型を宣言する
typedef int (*fptrOperation)(const char*, const char*);

// バブルソートアルゴリズムによるsort関数
void sort(char *array[], int size, fptrOperation operation){
	int i;
	int swap = 1;
	while(swap){
		swap = 0;
		for(i = 0; i < size-1; i++){
			// 関数ポインタによってcompare関数が呼び出されている
			if(operation(array[i], array[i+1]) > 0){
				swap = 1;
				char *tmp = array[i];
				array[i] = array[i+1];
				array[i+1] = tmp;
			}
		}
	}
}

// 表示用関数
void displayNames(char* names[], int size){
	int i;
	for(i = 0; i < size; i++){
		printf("%s   ", names[i]);
	}
	printf("\n");
}

int compare(const char* s1, const char* s2){
	return strcmp(s1, s2);
}

int main(){
	char* names[] = {"Bob", "Ted", "Carol", "Alice", "alice"};
	sort(names, 5, compare);
	displayNames(names, 5);
}
