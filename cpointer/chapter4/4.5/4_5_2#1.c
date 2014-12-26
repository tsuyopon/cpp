#include<stdio.h>

void displayArray1(int* arr, int size){
	printf("========== displayArray1 ===========\n");
	int i;
	for(i = 0; i < size; i++){
		printf("%d\n", arr[i]);
	}
}

void displayArray2(int* arr, int size){
	printf("========== displayArray2 ===========\n");
	int i;
	for(i = 0; i < size; i++){
		printf("%d\n", *(arr+i));
	}
}

void displayArray3(int arr[], int size){
	printf("========== displayArray3 ===========\n");
	int i;
	for(i = 0; i < size; i++){
		printf("%d\n", *(arr+i));
	}
}

int main(){
	int vector[5] = {1,2,3,4,5};
	displayArray1(vector, 5);
	displayArray2(vector, 5);
	displayArray3(vector, 5);
}
