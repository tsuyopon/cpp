#include<cstdio>
#include<cstdlib>
#include<cstring>

class Test {
	public:
		Test(){ p = new char[10]; }
		void test(void) const {}
	private:
		char* p;
};

char* leak_test(const char* s) {
	char* p = (char*)malloc(10);
	strcpy(p, s);
	free(p);
	return p;
}

int main(){
	int n;
	char* p = leak_test("0123456789");
	printf("p: %s\n", p);
	Test* t = new Test;
	t->test();
	if( n != 0 ){ printf("test\n"); }
	return 0;
}
