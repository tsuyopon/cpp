//IntArray.cpp

#include "IntArray.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace std;

//コピーコンストラクタの定義
IntArray :: IntArray(const IntArray &other)
{
    m_array = new int[other.m_size];   //配列の動的確保, otherオブジェクトの値を使う 
    m_size = other.m_size;                  //otherオブジェクトの値をコピーs
    
    copy(other.m_array, other.m_array + m_size, m_array);
    
    cout << "コピーコンストラクタが呼ばれました。" << endl;
}

//コンストラクタ
IntArray :: IntArray(int size)
{
    m_array = new int[size];
    m_size = size;

    cout << "コンストラクタが呼ばれました。"
            << "要素数は " << m_size << "です。" << endl;
}

//デストラクタ
IntArray :: ~IntArray()
{
    delete [] m_array;

    cout << "デストラクタが呼ばれました"
            << "要素数は" << m_size << "でした" << endl;
}

//メンバへのアクセス関数
int IntArray :: Get (int i) const                // added const
{
    CheckIndex(i);
    return m_array[i];
}

void IntArray :: Set(int i, int value)
{
    CheckIndex(i);
    m_array[i] = value;
}

//インデックスのチェック
void IntArray :: CheckIndex(int i) const          // added const
{
    if(i >= 0 && i < m_size)
    {
        //インデックスは正常です
    }
    else
    {
        cout << "インデックスが不正です" << endl
                << "値 : " << i << endl;
        exit(EXIT_FAILURE);
    }
}

int IntArray :: Size() const                 // added const
{
    return m_size;
}
