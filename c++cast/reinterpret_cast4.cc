// 構造体に格納してunsigned char*に強制的に変換してから、さらにバイナリ列を取り出す
#include<iostream>
#include <stdio.h>
#include <inttypes.h>

template <typename T>
T *get(unsigned char **pos){
    T *ret = reinterpret_cast<T *>(*pos);
    *pos += sizeof(T);
    return ret;
}

struct BinaryData  {
	uint8_t first;
	uint16_t second;
	uint8_t third;
	uint32_t forth;
} data;

int main(){
	static const uint8_t MYFIRST = 10;
	static const uint16_t MYSECOND = 1000;
	static const uint8_t MYTHIRD = 11;
	static const uint32_t MYFORTH = 32000;

	data.first = MYFIRST;
	data.second = MYSECOND;
	data.third = MYTHIRD;
	data.forth = MYFORTH;

	unsigned char* v = reinterpret_cast<unsigned char*>(&data);
	const auto getfirst  = get<decltype(MYFIRST)>(&v);
	const auto getsecond = get<decltype(MYSECOND)>(&v);
	const auto getthird  = get<decltype(MYTHIRD)>(&v);
	const auto getforth  = get<decltype(MYFORTH)>(&v);

	printf("%" PRIu8 "\n",data.first);
	printf("%" PRIu16 "\n",data.second);
	printf("%" PRIu8 "\n",data.third);
	printf("%" PRIu32 "\n",data.forth);

}
