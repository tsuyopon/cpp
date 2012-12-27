/*
 * 8/sample2のプログラムにてShowの引数を"IntArray array"から"const IntArray& array"に変更した
 *
 */

//Copy1.cpp
#include "IntArray.h"
#include <iostream>
using namespace std;

void Viss(int num)
{
    cout << "Viss : No." << num << endl;
}

void Show(const IntArray& array)              // added const and reference(&)
{
    Viss(2);
    
	cout << "array.Size() loop start" << endl;
    for(int i = 0; i < array.Size(); ++i)
    {
		cout << "array.Get(i) loop. i=" << i << endl;
        cout << array.Get(i) << ' ';
    }
    cout << endl;

    Viss(3);
}

int main()
{
	cout << "start main()" << endl;
    IntArray array0to9(10);
    
	cout << "start loop" << endl;
    for(int i = 0; i < array0to9.Size(); ++i)
    {
        array0to9.Set(i, i);
    }
	cout << "end loop" << endl;

	cout << "start Viss(1)" << endl;
    Viss(1);
	cout << "start show()" << endl;
    Show(array0to9);
	cout << "start Viss(4)" << endl;
    Viss(4);
	cout << "end main()" << endl;

}

