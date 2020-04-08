// [このプログラムの作成意図]
// 各種型がどのようにメモリ上に配置されるのかを確認するプログラム
// この基礎知識がないと別の型から、Nbyteだけ取得するといった事象を扱うのに混乱する。
//
// コメントにはメモリ配置を添付しています。これらの配置は実際にビット演算した際の並び順と異なることを確認してください。
//
// 参考: https://qiita.com/miz_erz/items/fdf3957549945746cb1b
#include<stdio.h>
#include <string.h> // memcpy
#include <stdint.h> // uint8_t

// 3byte data
struct uint24{
    unsigned int data : 24;
};

int main(){

	int local_int1 = 0xfafbfcfd;
	int local_int2 = 0x1;

	/////////////////////////////////////////////////////////////
	// コメント: メモリ配置を記述しているが手元のMACで確認
	/////////////////////////////////////////////////////////////



	/////////////////////////////////////////////////////////////
	// intの確認
	/////////////////////////////////////////////////////////////

	// (gdb) x/4bx &local_int1
	// 0x7fffffffdfbc:	0xfd	0xfc	0xfb	0xfa
	printf("int local_int1  = 0xfafbfcfd => %02x %02x %02x %02x\n", 
			((local_int1 >> 24) & 0xFF),
			((local_int1 >> 16) & 0xFF),
			((local_int1 >> 8) & 0xFF),
			((local_int1) & 0xFF)
	);

	// (gdb) x/4bx &local_int2
	// 0x7fffffffdfb8:	0x01	0x00	0x00	0x00
	printf("int local_int2  = 0x1 => %02x %02x %02x %02x\n", 
			((local_int2 >> 24) & 0xFF),
			((local_int2 >> 16) & 0xFF),
			((local_int2 >> 8) & 0xFF),
			((local_int2) & 0xFF)
	);

	/////////////////////////////////////////////////////////////
	// uintの確認
	/////////////////////////////////////////////////////////////
	unsigned int local_uint1 = 0xfafbfcfd;
	unsigned int local_uint2 = 0x1;

	// (gdb) x/4bx &local_uint1
	// 0x7fffffffdfb4:	0xfd	0xfc	0xfb	0xfa
	printf("int local_uint1 = 0xfafbfcfd => %02x %02x %02x %02x\n", 
			((local_uint1 >> 24) & 0xFF),
			((local_uint1 >> 16) & 0xFF),
			((local_uint1 >> 8) & 0xFF),
			((local_uint1) & 0xFF)
	);

	// (gdb) x/4bx &local_uint2
	// 0x7fffffffdfb0:	0x01	0x00	0x00	0x00
	printf("int local_uint2 = 0x1 => %02x %02x %02x %02x\n", 
			((local_uint2 >> 24) & 0xFF),
			((local_uint2 >> 16) & 0xFF),
			((local_uint2 >> 8) & 0xFF),
			((local_uint2) & 0xFF)
	);

	/////////////////////////////////////////////////////////////
	// uint24の確認(uint24はstructで定義されています)
	/////////////////////////////////////////////////////////////
	// (gdb) x/4bx &local_uint24_1.data
	// 0x7fffffffdfac:	0xfc	0xfb	0xfa	0x00
	uint24 local_uint24_1;
	local_uint24_1.data = 0xfafbfc;
	printf("uint24 local_uint24_1.data = 0xfafbfc => %02x %02x %02x\n", 
			((local_uint24_1.data >> 16) & 0xFF),
			((local_uint24_1.data >> 8) & 0xFF),
			((local_uint24_1.data) & 0xFF)
	);
	// このパターンの場合にも3byteパケットを構築するような場合には、1つずつchar配列に敷き詰める必要がありそう。


	/////////////////////////////////////////////////////////////
	// unsigned charの確認
	//
	// 連続したパケットを構築する場合には以下のchar配列のパターンしか適していない模様
	/////////////////////////////////////////////////////////////
	// (gdb) x/4bx &my_uchar
	// 0x7fffffffdfa8:	0xfa	0xfb	0xfc	0xfd
	unsigned char my_uchar[4];
	my_uchar[0] = 0xfa;
	my_uchar[1] = 0xfb;
	my_uchar[2] = 0xfc;
	my_uchar[3] = 0xfd;
	printf("unsigned char my_uchar[4] = 0xfa, 0xfb, 0xfc, 0xfd => %02x %02x %02x %02x\n", my_uchar[0], my_uchar[1], my_uchar[2], my_uchar[3]);

}
