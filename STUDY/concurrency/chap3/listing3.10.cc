// 意味の無い比較を行っている例
// 必要なロックは全体にかけるべきという教訓となるプログラム
// ある時点のlhsとある時点のrhsを比較しているので全く意味がない処理を実施している事になる。
// このように必要な処理に対して全体をロックしないとレースコンディションとなることを意識する必要がある。

#include<iostream>
class Y
{
private:
    int some_detail;
    mutable std::mutex m;
    int get_detail() const
    {
		std::cout << "start get_detail()" << std::endl;
        std::lock_guard<std::mutex> lock_a(m);
		std::cout << "end get_detail()" << std::endl;
        return some_detail;
    }
public:
    Y(int sd):some_detail(sd){}
    friend bool operator==(Y const& lhs, Y const& rhs)
    {
		std::cout << "operator==" << std::endl;
		if(&lhs==&rhs)
   			return true;
		int const lhs_value=lhs.get_detail();
		int const rhs_value=rhs.get_detail();
		return lhs_value==rhs_value;
	}
};

int main(){
	Y y(3);
	Y x(3);
	if(x == y){
		std::cout << "true" << std::endl;
	} else {
		std::cout << "false" << std::endl;
	}
}
