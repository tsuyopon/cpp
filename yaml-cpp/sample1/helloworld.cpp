#include "yaml-cpp/yaml.h"

int main(){
	YAML:: Emitter out;
	out << "Hello, world";

	std::cout << "output" << out.c_str();
	return 0;
}
