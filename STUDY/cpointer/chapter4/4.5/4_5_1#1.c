#include<stdio.h>

void displayArray(int arr[], int size){
	int i;
	for(i = 0; i < size; i++){
		printf("%d\n", arr[i]);
	}
}

int main(){
	int vector[5] = {1, 2, 3, 4, 5};
	displayArray(vector, sizeof(vector)/sizeof(int));
}
