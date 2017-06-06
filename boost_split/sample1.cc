#include <boost/algorithm/string.hpp>
#include <string>
#include <list>
#include <iostream>
 
#include <boost/foreach.hpp>
using namespace std;
int
main ()
{

	// 1. space区切り
	std::cout << "CASE1:" << std::endl;
    string str1 ("192.168.0.1 192.168.0.2");
    list<string> list_string1;
    boost::split(list_string1, str1, boost::is_space());
    BOOST_FOREACH(string s, list_string1) {
    	cout << s << endl;
    }

	// 2. 別の文字で区切る
	std::cout << std::endl << "CASE2:" << std::endl;
    string str2 = "192.168.0.1";
	vector<string> v2;
	boost::algorithm::split(v2, str2, boost::is_any_of("."));
    BOOST_FOREACH(string s, v2) {
    	cout << s << endl;
    }

	// 3. 複数のデリミタを指定する場合
	std::cout << std::endl << "CASE3:" << std::endl;
	std::string str3 = "2011/02/09 20:19:33";
	std::list<std::string> results3;
	//スラッシュ、スペース、コロンで分割
	boost::split(results3, str3, boost::is_any_of("/ :"));
	BOOST_FOREACH(string s, results3) {
		  std::cout << s << std::endl;
	}

    return 0;
}
