#include<cstdio>
#include<cstdlib>
#include<cstring>

class Test {
	public:
		Test(){ p = new char[10]; }
		void test(void) const {}
		virtual ~Test() { delete[] p; }
	private:
		char* p;
};

char* leak_test(const char* s) {
	char* p = (char*)malloc(10);
	*p = '\0';
	strncat(p, s, 9);
	free(p);
	return p;
}

int main(){
	int n;
	char* p = leak_test("0123456789");
	printf("p: %s\n", p);
	free(p);

	Test* t = new Test;
	t->test();
	delete t;

	if( n != 0 ){ printf("test\n"); }
	return 0;
}
