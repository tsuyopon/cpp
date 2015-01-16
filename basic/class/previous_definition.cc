#include<iostream>
using namespace std;

/*
 * 前方宣言について
 */

class Man;                // 前方宣言

class Human {
	public:
		Human(Man &);     // Manというのを知らせるためにそれよりも前の行で前方宣言している
};

class Man {
	public:
		char *name;
		Man(char *name){
			Man::name = name;
		}
} manobj("azarashi");

Human::Human(Man &obj){
	cout << obj.name << endl;
}

int main(){
	Human obj(manobj); 
	return 0;
}
