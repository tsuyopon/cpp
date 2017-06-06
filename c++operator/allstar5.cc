class CPoint3d
{
public:
	double x, y, z;
	CPoint3d(double a = 0, double b = 0, double c = 0) : x(a), y(b), z(c) {}
	// 代入演算（「=」）
	CPoint3d& operator = ( const CPoint3d& b )
	{
		x = b.x; y = b.y; z = b.z;
		return *this;
	}
	// 和差積商（「+」「-」「*」「/」）
	const CPoint3d operator + ( const CPoint3d& b ) const
	{
		return CPoint3d( x + b.x, y + b.y, z + b.z );
	}
	// 自身に対する和差積商（「+=」「-=」「*=」「/=」）
	CPoint3d& operator += ( const CPoint3d& b )
	{
		x += b.x; y += b.y;	z += b.z;
		return *this;
	}
	// 比較演算（「==」「!=」「<」「>」）
	bool operator == ( const CPoint3d& b ) const
	{
		return (x == b.x && y == b.y && z == b.z );
	}
	// 配列アクセス（「[ ]」）
	const double& operator [] ( const long i ) const	// 読み取り用
	{
		return *((&x) + i);
	}
	double& operator [] ( const long i )	// 書き込み用
	{
		return *((&x) + i);
	}

};

int main()
{
	CPoint3d point1(1,1,1), point2(2,2,2), point3(3,3,3);
	int i1 = 1, i2 = 2, i3 = 3;

	// 代入演算（「=」）
	point1 = point2 = point3;
	i1 = i2 = i3;	// コンパイル可

	(point1 = point2) = point3;
	(i1 = i2) = i3;	// コンパイル可

	// 和差積商（「+」「-」「*」「/」）
	// (point1 + point2) = point3;
	// (i1 + i2) = i3;	// コンパイルエラー

	// 自身に対する和差積商（「+=」「-=」「*=」「/=」）
	point1 += point2 += point3;
	i1 += i2 += i3;	// コンパイル可

	(point1 += point2) = point3;
	(i1 += i2) = i3;	// コンパイル可

	// 比較演算（「==」「!=」「<」「>」）
	// (point1 == point2) = true;
	// (i1 = i2) = true;	// コンパイルエラー

	// 配列アクセス（「[ ]」）
	const CPoint3d point4(4,4,4);
	point1[0] = point4[0];
	// point4[0] = point1[0];	// コンパイルエラー

	return 0;
}

