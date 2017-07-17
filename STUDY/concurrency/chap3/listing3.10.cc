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
