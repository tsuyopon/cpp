#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<clocale>

using namespace std;

int main(void){
	char *s = (char*)"testsテスト";
	int len, i = 0;

	setlocale(LC_CTYPE, "ja_JP.UTF-8");
	while(s[i] != '\0'){
		len = mblen(&s[i], MB_CUR_MAX);
		printf("%d ", len);
		i += len;
	}
	cout << endl << "COUNTBYTE:" << i << endl;
	return 0;
}
