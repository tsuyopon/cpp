#include <stdio.h>

int main(void){
	int i = 100;
	FILE *file;
	const char* writename = "writefile.txt";
	file = fopen(writename, "w");
	fprintf(file, "%d", i);
	printf("CREATING %s\n", writename);
	fclose(file);
	return 0;
}
