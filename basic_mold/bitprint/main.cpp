// sample to put binary data
#include "bitStreamPointer.h"
#include <iostream>

using std::cout;
using std::endl;

int main ( void )
{
	std::vector<unsigned char> data;
	for ( unsigned char i = 0; i < 10; i++)
	{
		data.push_back( i );
	}

	bitStreamPointer bsp( data );
	unsigned char bit = 0;
	int i = 0;
	while ( bsp.getBit( bit ) )
	{
		cout << (int)bit;
		bsp.posBitNext();
	}

	return 0;

}
