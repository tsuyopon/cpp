#include <iostream>
#include <string>
using namespace std;

int main(){
	while(true){
		string line;
		cout << "Input Character --> " << flush;

		// line parameter is string class.
		// If this type were char, we would consider about max size. Example char line[100].
		getline(cin, line);

		// string type can compare "==" operator. we don't need use strcmp().
		if(line == "quit"){     
			break;
		}

		string::size_type pos = line.rfind(".");   // search character from tail.
		if(pos == string::npos){                   // no character matching.
			line += "azarashi";
		} else {
			line.insert(pos, "aaa");
		}

		cout << line << endl;
	}
}
