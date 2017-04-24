#include <vector>
#include <iostream>

class bitStreamPointer{
private:
	// データ始端
	unsigned char *start;
	// データ終端
	unsigned char *end;
	// バイト座標．0, 1, ...
	size_t posByte;
	// ビット座標．0, 1, 2, 3, 4, 5, 6, 7
	size_t posBit;
	// ビットマスク．start[x] との論理積を計算するために使用する
	unsigned char bitMask;
	// データ終端フラグ
	bool isEndPoint;

public:
	/** コンストラクタ
	*/
	bitStreamPointer( std::vector<unsigned char> &src )
	{
		start = &(src[0]);
		end = start + src.size();
		posByte = 0;
		posBit = 0;
		bitMask = 1;
		isEndPoint = false;
	}

	/** バイトデータを得る
	@return 成否
	*/
	bool getByte( unsigned char &byte)
	{
		// 終端検査
		if ( isEndPoint )
		{
			return !isEndPoint;
		}
		byte = start[posByte];
		return !isEndPoint;
	}

	/** ビットデータを得る
	@return 成否
	*/
	bool getBit( unsigned char &bit )
	{
		// 終端検査
		if ( isEndPoint )
		{
			return !isEndPoint;
		}
		// マスクして右シフト
		bit = (start[posByte] & bitMask) >> posBit;

		return !isEndPoint;
	}

	/** 注目バイトを進める 
	@return 成否
	*/
	bool posByteNext()
	{
		// 終端検査
		if ( isEndPoint )
		{
			return !isEndPoint;
		}
		// バイト位置インクリメント
		posByte++;
		// 終端検査
		if ( &start[posByte] == end )
		{
			isEndPoint = true;
		}
		return !isEndPoint;
	}

	/** 注目ビットを進める
	@return 成否
	*/
	bool posBitNext()
	{
		// 終端検査
		if ( isEndPoint )
		{
			return !isEndPoint;
		}
		// ビット位置インクリメント
		posBit++;
		// ビットマスク対応
		bitMask <<= 1;
		// 全ビットを確認していた場合，バイト位置インクリメント
		if ( posBit == 8 )
		{
			// ビット位置初期化
			posBit = 0;
			// ビットマスク初期化
			bitMask = 1;
			// 注目バイトを進める
			posByteNext();
		}
		return !isEndPoint;
	}

};
