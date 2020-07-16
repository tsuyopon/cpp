//
// compile
//  $ g++ sample17_1.cc -std=c++17
#include<iostream>
#include<map>

int main(){
	std::map<std::string, std::string> headers;
	headers[":method"] = "GET";
	headers[":path"] = "/";
	headers[":scheme"] = "https";
	headers[":authority"] = "www.google.com";

	for (const auto& [key, value] : headers){
		std::cout << key << " => " << value << "\n";
	}
}
