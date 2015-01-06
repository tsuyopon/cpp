#include<stdio.h>
#include<stdlib.h>

float average(int *arr, int size){
	int i;
	int sum=0;
	printf("arr: %p\n",  &arr);
	printf("size: %p\n", &size);
	printf("sum: %p\n",  &sum);

	for(i=0; i<size; i++){
		sum += arr[i];
	}
	return (sum * 1.0f) / size;
}

int main(){
	float ret;
	int arr[5] = {1, 2, 3, 4, 5};
	ret = average(arr, sizeof(arr)/sizeof(float));
	printf("%f\n", ret);
}
