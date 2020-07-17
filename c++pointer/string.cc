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


/*
 * 
 *  以下のドキュメントを参照のこと
 *
 *  best way to return an std::string that local to a function
 *  See: https://stackoverflow.com/questions/3976935/best-way-to-return-an-stdstring-that-local-to-a-function
 */

// この場合の戻り値はローカルスコープでout of scopeにはならず、mystringのコピーが返されるようになるらしい。
std::string returnByValue()
{
    std::string mystring("returnByValue");
    return mystring;

}

// アドレスと参照を戻す方法の場合にはnewが必要
// see: https://www.quora.com/How-do-you-return-std-string-from-a-function-in-C
std::string* returnByAddress() {
    std::string *mystring = new std::string("returnByAddress");   // アドレスや参照をreturnする場合にはnewしないとだめ!!!
    return mystring;
}

// アドレスと参照を戻す方法の場合にはnewが必要
std::string& returnByReference() {
    std::string *mystring = new std::string("returnByReference");   // アドレスや参照をreturnする場合にはnewしないとだめ!!!
    return *mystring;  // 参照なので*をつける
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

	// returnByValueの確認
	std::cout << "===================== returnByValue =====================" << std::endl;
	std::cout << "In main: " << returnByValue() << std::endl << std::endl;

	// returnByAddressの確認
	std::cout << "===================== returnByAddress =====================" << std::endl;
	std::cout << "In main: " << *(returnByAddress()) << std::endl << std::endl;

	// returnByReferenceの確認
	std::cout << "===================== returnByReference =====================" << std::endl;
	std::cout << "In main: " << returnByReference() << std::endl << std::endl;

}
