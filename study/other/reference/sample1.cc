#include <stdio.h>

int main(){
	int var;
	int& ref = var;       // Define reference.
	ref = 1;
	printf("%d\n", var);
	return true;
}	
