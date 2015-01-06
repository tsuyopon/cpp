#include<stdio.h>

int main(){
	int matrix[2][3] = {{1,2,3},{4,5,6}};
	int i;
	for(i = 0; i < 2; i++){
		printf("&matrix[%d]: %p sizeof(matrix[%d]): %d\n", i, &matrix[i], i, sizeof(matrix[i]));
	}
}
