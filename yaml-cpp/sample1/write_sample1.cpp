/*
 * yaml write sample.
 *
 * See http://code.google.com/p/yaml-cpp/wiki/HowToEmitYAML
 */
#include "yaml-cpp/yaml.h"

int main(){

	// Initialization
	YAML:: Emitter out;

	// list
	out << YAML::BeginSeq;
	out << "eggs";
	out << "break";
	out << "milk";
	out << YAML::EndSeq;

	// maps
	out << YAML::BeginMap;
	out << YAML::Key << "name";
	out << YAML::Value << "tsuyoshi";
	out << YAML::Key << "age";
	out << YAML::Value << "31";
	out << YAML::Key << "live";
	out << YAML::Value << "saitama";
	out << YAML::EndMap;

	// nested maps
	out << YAML::BeginMap;
	out << YAML::Key << "name";
	out << YAML::Value << "tsuyoshi";
	out << YAML::Key << "children";
	out << YAML::Value << YAML::BeginSeq << "chappy" << "yuuta" << YAML::EndSeq;
	out << YAML::EndMap;

	// Literal
	out << YAML::Literal << "A\n B\n C";

	// Flow
	out << YAML::Flow;
	out << YAML::BeginSeq << 2 << 3 << 4 << 5 << 6 << YAML::EndSeq;

	// Aliases adn Anchors
	out << YAML::BeginSeq;
	out << YAML::Anchor("fred");
	out << YAML::BeginMap;
	out << YAML::Key << "name" << YAML::Value << "tsuyoshi";
	out << YAML::Key << "age" << YAML::Value << "20";
	out << YAML::EndMap;
	out << YAML::Alias("tsuyoshi");
	out << YAML::EndSeq;

	// Finalizer
	std::cout << out.c_str()<< std::endl;

	return 0;
}
