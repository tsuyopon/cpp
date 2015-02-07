#include <stdio.h>

int main(void){
	int i;
	FILE *file;
	const char* readname = "readfile.txt";
	file = fopen(readname, "r");
	fscanf(file, "%d", &i);
	fclose(file);
	printf("%d\n", i);
	return 0;
}

