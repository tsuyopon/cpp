#include <iostream>
#include <vector>
using namespace std;

int main(){
	vector<int> v(10);
	for(size_t i = 0, size = v.size(); i < size; ++i){
		v[i] = i * i;
	}

	v.resize(5);
	for(size_t i = 0, size = v.size(); i < size; ++i){
		cout << v[i] << ' ';
	}
	cout << endl;
}
