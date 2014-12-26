#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void displayHeader(){
	static char*staticHeader = "Chapter";                    // 大域変数
	char* localHeader = "Chapter";                           // 局所変数
	static char staticArrayHeader[] = "Chapter";             // 大域変数
	char localArrayHeader[] = "Chapter";                     // 局所変数
	char *heapHeader = (char*)malloc(strlen("Chapter"+1));   // 局所変数
	strcpy(heapHeader, "Chapter");
}
int main(){
	char *globalHeader = "Chapter";                          // 大域変数
	char globalArrayHeader[] = "Chapter";                    // 大域変数
}
