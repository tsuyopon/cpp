// 構造体に格納してunsigned char*に強制的に変換してから、さらにバイナリ列を取り出す
// reinterpret_cast4_1.ccの誤りを修正した正しいプログラムとなる
//
// gdbで値を確認したら次のようになる。
// (gdb) p v
// $1 = (unsigned char *) 0x601064 <data> "\n\v\350\003"
// (gdb) x/3x v
// 0x601064 <data>:	0x03e80b0a	0x00007d00	0x00000000
//  
// 先程のreinterpret_cast4.ccと異なり2byteに収まっていることに注目すること。これはパディングの問題となる。
//  0x03e8     = 1000
//  0x0b       = 11
//  0x0a       = 10
//  0x00007d00 = 32000
//

#include<iostream>
#include <stdio.h>
#include <inttypes.h>

template <typename T>
T *get(unsigned char **pos){
    T *ret = reinterpret_cast<T *>(*pos);
    *pos += sizeof(T);
    return ret;
}

// NOTE: 構造体の詰替順が先程のreinterpret_cast4_1.ccとは異なることに注意する。
struct BinaryData  {
	uint8_t first;
	uint8_t second;
	uint16_t third;
	uint32_t forth;
} data;

int main(){
	static const uint8_t MYFIRST = 10;
	static const uint8_t MYSECOND = 11;
	static const uint16_t MYTHIRD = 1000;
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

	/*
	 * 例えば、uint32_tの変換の場合
	 * printf("%" PRIu32 "\n", *reinterpret_cast<uint32_t*>( const_cast<unsigned char*>(getforth) ));
	 * と記述してコンパイルすると次のエラーが表示される。
	 *
	 * $ g++ reinterpret_cast5.cc 
	 * reinterpret_cast5.cc: In function ‘int main()’:
	 * reinterpret_cast5.cc:56:96: error: invalid const_cast from type ‘const unsigned int* const’ to type ‘short unsigned int*’
	 *   printf("%" PRIu32 "\n", *reinterpret_cast<uint32_t*>( const_cast<short unsigned int*>(getforth) ));
	 *
	 * 「const unsigned int* const」からconstを取って「unsigned int*」に変換するにはconst_cast<unsigned int*>(getforth)となる。
	 * さらにこのポインタをuint32_t*に変換する。これはreinterpret_cast(これはポインタ通しの変換しかできない)
	 *  reinterpret_cast<uint32_t*>( const_cast<unsigned int*>(getforth) )
	 * となりこの値が欲しいので*を付与して
	 *  *reinterpret_cast<uint32_t*>( const_cast<unsigned int*>(getforth) )
	 * となる
	 *
	 */
	printf("%" PRIu8 "\n",  *reinterpret_cast<uint8_t*>(  const_cast<unsigned char*>(getfirst) ));
	printf("%" PRIu8 "\n",  *reinterpret_cast<uint8_t*>(  const_cast<unsigned char*>(getsecond) ));
	printf("%" PRIu16 "\n", *reinterpret_cast<uint16_t*>( const_cast<short unsigned int*>(getthird) ));
	printf("%" PRIu32 "\n", *reinterpret_cast<uint32_t*>( const_cast<unsigned int*>(getforth) ));

	// 参考までに構造体の値も直接出力しておく
	printf("%" PRIu8 "\n",data.first);
	printf("%" PRIu8 "\n",data.second);
	printf("%" PRIu16 "\n",data.third);
	printf("%" PRIu32 "\n",data.forth);

}
