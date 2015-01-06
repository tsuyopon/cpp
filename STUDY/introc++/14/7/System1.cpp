#include<iostream>
#include<cstdlib>

using namespace std;

#ifdef WINDOWS
#define CURRENT
#else
#define CURRENT "./"
#endif

const char FILENAME[] = CURRENT "Main1";

int main(){
	if(system(FILENAME) == 0){
		cout << "Success Execution" << endl;
		return EXIT_SUCCESS;
	} else {
		cerr << "Failed Execution" << endl;
		return EXIT_FAILURE;
	}

}
