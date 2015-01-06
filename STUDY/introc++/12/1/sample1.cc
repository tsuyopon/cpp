#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <bitset>
#include <string>
using namespace std;

std::string ul_to_bin(unsigned long n) {
	return std::bitset<32>(n).to_string<char,std::char_traits<char>,std::allocator<char> >();
}

unsigned long bin_to_ul(const std::string& s) {
	return std::bitset<8>(s).to_ulong();
}

int main(){

	string a, b;
	long int data1, data2;

	a = "11111111";
	b = "10110101";
	data1 = strtol(a.c_str(), NULL, 2);
	data2 = strtol(b.c_str(), NULL, 2);

	cout << "a=" << bin_to_ul(a.c_str()) << ", b=" << bin_to_ul(b.c_str()) << endl;
	cout << "data1=" << data1 << ", data2=" << data2 << endl;
	cout << "(data1 & data2) = " << (data1 & data2) << endl;
	cout << ul_to_bin(data1 & data2) << endl;

}
