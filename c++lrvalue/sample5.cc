// 型Tが左辺値参照型、右辺値参照型かを調べる
#include <type_traits>
int main(){

	// lvalue
	static_assert(std::is_lvalue_reference<int&>::value == true, "value == true, int& is lvalue reference");
	static_assert(std::is_same<std::is_lvalue_reference<int&>::value_type, bool>::value, "value_type == bool");
	static_assert(std::is_same<std::is_lvalue_reference<int&>::type, std::true_type>::value, "type == true_type");
	static_assert(std::is_lvalue_reference<int&>() == true, "is_lvalue_reference<int&>() == true");

	static_assert(std::is_lvalue_reference<int>::value == false, "value == false, int is not lvalue reference");
	static_assert(std::is_same<std::is_lvalue_reference<int>::value_type, bool>::value, "value_type == bool");
	static_assert(std::is_same<std::is_lvalue_reference<int>::type, std::false_type>::value, "type == false_type");
	static_assert(std::is_lvalue_reference<int>() == false, "is_lvalue_reference<int>() == false");

	static_assert(std::is_lvalue_reference<unsigned&>::value == true, "unsigned& is lvalue reference");
	static_assert(std::is_lvalue_reference<const long&>::value == true, "const long& is lvalue reference");
	static_assert(std::is_lvalue_reference<const double*&>::value == true, "const double*& is lvalue reference");
	static_assert(std::is_lvalue_reference<void (&)()>::value == true, "void (&)() is lvalue reference");

	static_assert(std::is_lvalue_reference<int*>::value == false, "int* is not lvalue reference");
	static_assert(std::is_lvalue_reference<int&&>::value == false, "int&& is not lvalue reference");
	static_assert(std::is_lvalue_reference<void ()>::value == false, "void () is not lvalue reference");
	static_assert(std::is_lvalue_reference<void (int&)>::value == false, "void (int&) is not lvalue reference");

	// rvalue
	static_assert(std::is_rvalue_reference<int&&>::value == true, "value == true, int&& is rvalue reference");
	static_assert(std::is_same<std::is_rvalue_reference<int&&>::value_type, bool>::value, "value_type == bool");
	static_assert(std::is_same<std::is_rvalue_reference<int&&>::type, std::true_type>::value, "type == true_type");
	static_assert(std::is_rvalue_reference<int&&>() == true, "is_rvalue_reference<int&&>() == true");
	
	static_assert(std::is_rvalue_reference<int>::value == false, "value == false, int is not rvalue reference");
	static_assert(std::is_same<std::is_rvalue_reference<int>::value_type, bool>::value, "value_type == bool");
	static_assert(std::is_same<std::is_rvalue_reference<int>::type, std::false_type>::value, "type == false_type");
	static_assert(std::is_rvalue_reference<int>() == false, "is_rvalue_reference<int>() == false");
	
	static_assert(std::is_rvalue_reference<unsigned&&>::value == true, "unsigned&& is rvalue reference");
	static_assert(std::is_rvalue_reference<const long&&>::value == true, "const long&& is rvalue reference");
	static_assert(std::is_rvalue_reference<const double*&&>::value == true, "const double*&& is rvalue reference");
	static_assert(std::is_rvalue_reference<void (&&)()>::value == true, "void (&&)() is rvalue reference");
	
	static_assert(std::is_rvalue_reference<int*>::value == false, "int* is not rvalue reference");
	static_assert(std::is_rvalue_reference<int&>::value == false, "int& is not rvalue reference");
	static_assert(std::is_rvalue_reference<void ()>::value == false, "void () is not rvalue reference");
	static_assert(std::is_rvalue_reference<void (int&&)>::value == false, "void (int&&) is not rvalue reference");
}
