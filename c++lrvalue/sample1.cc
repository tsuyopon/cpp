// なお、C++98のreferenceは、C++0xにおいては、lvalue referenceと呼ばれるものである。 
// rvalueの宣言は&で、lvalueの宣言は&&を使う用になっています。
struct X{ } ;

int main()
{
	X x ;

	// lvalue reference
	X &lr1 = x;           // OK: xはlvalue
	//X & lr2 = X();       // NG: X()はrvalueで、lvalue referenceでは参照することができない

	// rvalue reference
	//X && rr1 = x;        // NG: xはlvalue referenceなのでrvalueには入れられない
	X &&rr2 = X();        // OK: X()はrvalueなので問題ない rvalueはアンパサンドを２つ使う文法となっています。



}
