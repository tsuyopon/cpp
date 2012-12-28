/*
 * 何ビット目が1か0かをチェックするプログラム
 *
 */
#include <iostream>
#include <bitset>
#include <string>
using namespace std;

std::string ul_to_bin(unsigned long n) {
	return std::bitset<8>(n).to_string<char,std::char_traits<char>,std::allocator<char> >();
}

unsigned long bin_to_ul(const std::string& s) {
	return std::bitset<8>(s).to_ulong();
}

int main(){

	string a, b;
	long int data1, data2;

	a = "00101000";
	data1 = bin_to_ul(a.c_str());
	cout << "a=" << a.c_str() << endl;

	for(int i = 1; i < 256; i <<= 1){
		if( (data1 & i) == 0 ){
			cout << i << " is 0" << endl;
		} else {
			cout << i << " is 1" << endl;
		}
	}


//	cout << "(data1 << 2) =" << (data1 << 2) << endl;
//	cout << "(data1 >> 2) =" << (data1 >> 2) << endl;
//	cout << ul_to_bin(data1 << 2) << endl;
//	cout << ul_to_bin(data1 >> 2) << endl;

}
