#include<stdio.h>

int main(){
	int arr3d[3][2][4] = {
		{{1,2,3,4},{5,6,7,8}},
		{{9,10,11,12},{13,14,15,16}},
		{{17,18,19,20},{21,22,23,24}}
	};

	int i,j,k;
	for(i=0; i < 3; i++){
		for(j=0; j < 2; j++){
			for(k=0; k < 4; k++){
				printf("i=%d, j=%d, k=%d: value=%d\n", i, j, k, arr3d[i][j][k]);
			}
		}
	}
	return 0;
}
