// std::stringの値渡し、参照渡し、ポインタ渡しのサンプルです
// これらを確認すると参照渡しが最も理解しやすいことがわかります。
#include<string>
#include<iostream>

void passByValue(std::string teststr){
	teststr = "passByValue";
	std::cout << "In passByReference: " << teststr << std::endl;
}

void passByReference(std::string &teststr){
	teststr = "passByReference";
	std::cout << "In passByReference: " << teststr << std::endl;
}

void passByPointer(std::string *teststr){
	*teststr = "passByPointer";
	std::cout << "In passByPointer: " << *teststr << std::endl;
}


int main(){

	// passByValueの確認
	std::cout << "===================== passByValue =====================" << std::endl;
	std::string teststr1 = "main";
	std::cout << "In main: " << teststr1 << std::endl;
	passByValue(teststr1);
	std::cout << "In main: " << teststr1 << std::endl << std::endl;

	// passByReferenceの確認
	std::cout << "===================== passByReference =====================" << std::endl;
	std::string teststr2 = "main";
	std::cout << "In main: " << teststr2 << std::endl;
	passByReference(teststr2);
	std::cout << "In main: " << teststr2 << std::endl << std::endl;

	// passByPointerの確認
	std::cout << "===================== passByPointer =====================" << std::endl;
	std::string teststr3 = "main";
	std::cout << "In main: " << teststr3 << std::endl;
	passByPointer(&teststr3);
	std::cout << "In main: " << teststr3 << std::endl << std::endl;

}
