#include<iostream>
#include<vector>
using namespace std;

int main(){
	// part1: push_backで詰め込む
	std::vector<unsigned int> uivec;
	uivec.push_back(16);
	uivec.push_back(2);
	uivec.push_back(77);
	uivec.push_back(29);
	uivec.push_back(35000);
	for (std::vector<unsigned int>::const_iterator i = uivec.begin(); i != uivec.end(); ++i)
		std::cout << *i << ' ';
	std::cout << std::endl;

	// part2: {}で詰め込む
	static const unsigned int arr[] = {16,2,77,29,35000};
	vector<unsigned int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	for (std::vector<unsigned int>::const_iterator i = vec.begin(); i != vec.end(); ++i)
		std::cout << *i << ' ';
	std::cout << std::endl;

	// part3: int32_t
	vector<int32_t> vec32t (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	for (std::vector<int32_t>::const_iterator i = vec32t.begin(); i != vec32t.end(); ++i)
		std::cout << *i << ' ';
	std::cout << std::endl;

	// part4: uint32_t
	vector<uint32_t> vecu32t (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	for (std::vector<uint32_t>::const_iterator i = vecu32t.begin(); i != vecu32t.end(); ++i)
		std::cout << *i << ' ';
	std::cout << std::endl;

	// part5: int8_t
	vector<int8_t> vec8t (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	for (std::vector<int8_t>::const_iterator i = vec8t.begin(); i != vec8t.end(); ++i)
		std::cout << signed(*i) << ' ';         // signedでかこまないとおかしくなる
	std::cout << std::endl;

	// part6: uint8_t
	vector<uint8_t> vecu8t (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	for (std::vector<uint8_t>::const_iterator i = vecu8t.begin(); i != vecu8t.end(); ++i)
		std::cout << unsigned(*i) << ' ';       // unsignedで囲まないとおかしくなる
	std::cout << std::endl;
}
