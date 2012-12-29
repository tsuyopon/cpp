#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

class Util{
	public:
		static std::string getNowTime(){
			char d[32];
			string date;
			sprintf(d, "%ld", time(NULL));
			date = string(d);
			return date;
		}
};
int main(){
	cout << Util::getNowTime() << endl;
}
