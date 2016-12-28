// 参考
// http://wisdom.sakura.ne.jp/programming/cpp/cpp27.html
#include<iostream>

using namespace std;

/*
 * オーバーロードできる演算子
 * +	-	*	/	%	^
 * !	=	<	>	+=	-=
 * ^=	&=	|=	<<	>>	<<=
 * <=	>=	&&	||	++	--
 * ( )	[ ]	new	delete	&	|
 * ~ 	*=	/=	%=	>>=	==
 * !=	,	->	->* 
 */
class Integer {
		int value;
	public:
		int operator + (Integer obj){
			cout << "called + operator"  << endl;
			return this->value + obj.value;  // 左辺のオペランド(この例ではobj1)は暗黙的にthisポインタで渡される
		}
		int operator * (Integer obj){
			cout << "called * operator"  << endl;
			return this->value * obj.value;  // 左辺のオペランド(この例ではobj1)は暗黙的にthisポインタで渡される
		}
		Integer(int value){ 
			cout << "called Integer class. value=" << value  << endl;
			this->value = value;
		}
};

int main(){
	Integer obj1(10), obj2(100);
	cout << obj1 + obj2 << endl;
	cout << obj1 * obj2 << endl;
	return 0;
}
