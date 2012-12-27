#ifndef FRACTION_H_
#define FRACTION_H_

class Fraction {
	public:
		Fraction(double numer = 0, double denom = 1);
	public:
		double GetNumer() const;   // 分子の取得
		double GetDenom() const;   // 分母の取得

	// オーバーロード定義
	public:
		operator double() const;
		Fraction operator*(const Fraction& rop);
		Fraction operator-() const;
		Fraction& operator*=(const Fraction& rop);
		Fraction& operator++();
		Fraction& operator++(int);

	private:
		double m_numer;
		double m_denom;
};

#endif   // #ifndef FRACTION_H_
