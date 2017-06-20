// 構造体に格納してunsigned char*に強制的に変換してから、さらにバイナリ列を取り出す
//  このプログラムはうまくパディングされていないので致命的なミスがある。
//
// gdbで値を確認した
//  (gdb) p v
//  $5 = (unsigned char *) 0x601064 <data> "\n"
//  (gdb) x/3x v
//  0x601064 <data>:	0x03e8000a	0x0000000b	0x00007d00
//  
// 上記を元にして
//  0x03e8     = 1000
//  0x000a     = 10    ※実はuint8_tなので下２桁だけ使われて
//  0x0000000b = 11
//  0x00007d00 = 32000
//
//  uint8_t, uint8_t, uint16_t, uint32_tの順番で構造体を並べれば2byteしか使わなかったはず。

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

	// 出力される値はおかしくなる。(これはパディングがあるためにgetが正しく動作していない)
	printf("%" PRIu8 "\n",  *reinterpret_cast<uint8_t*>(  const_cast<unsigned char*>(getfirst) ));
	printf("%" PRIu16 "\n", *reinterpret_cast<uint16_t*>( const_cast<short unsigned int*>(getsecond) ));
	printf("%" PRIu8 "\n",  *reinterpret_cast<uint8_t*>(  const_cast<unsigned char*>(getthird) ));
	printf("%" PRIu32 "\n", *reinterpret_cast<uint32_t*>( const_cast<unsigned int*>(getforth) ));

	// 上記の結果との比較のために構造体の値を直接出力しておく
	printf("%" PRIu8 "\n",data.first);
	printf("%" PRIu16 "\n",data.second);
	printf("%" PRIu8 "\n",data.third);
	printf("%" PRIu32 "\n",data.forth);
}
