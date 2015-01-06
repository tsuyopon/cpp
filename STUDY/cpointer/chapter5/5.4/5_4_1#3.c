#include<stdio.h>

char* staticFormat(const char* name, size_t quantity, size_t weight){
	static char buffer[64];
	sprintf(buffer, "Item: %s, Quantity: %u, Weight: %u", name, quantity, weight);
	return buffer;
}

int main(){
	char *part1 = staticFormat("Axle", 25, 45);
	printf("part1=%s\n", part1);
	char *part2 = staticFormat("Piston", 55, 5);
	printf("part1=%s\n", part1);
	printf("part2=%s\n", part2);
}
