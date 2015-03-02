//IntArray.h
#ifndef INTARRAY_H_20070101
#define INTARRAY_H_20070101

class IntArray
{
public:
    //コピーコンストラクタ
    IntArray(const IntArray &other);

	// [Point] 代入演算子のオーバーロード
	void operator=(const IntArray& other);
        
public:
    //コンストラクタ・デストラクタ
    IntArray(int size);
    ~IntArray();

public:
    //配列のサイズを返す
    int Size();

public:
    //メンバへのアクセス関数
    int Get(int i);
    void Set(int i, int value);

private:
    //インデックスのチェック
    void CheckIndex(int i);

private:
    int *m_array;    //動的配列
    int m_size;      //配列の要素数
};
#endif  //#ifndef INTARRAY_H_20070101
