#include <iostream>
using namespace std;

const int MAX_NAME = 16;

struct Student {
	char name[MAX_NAME + 1];
	int scoreJapanese;
	int scoreMath;
	int scoreEnglish;
};

void Show(const Student& student){
	cout << "NAME: " << student.name << endl
		<<  "  Japanese: " << student.scoreJapanese
		<<  ", Math: " << student.scoreMath
		<<  ", English: " << student.scoreEnglish 
		<< endl;
}

int main(){
	Student student[] = {
		{"taro", 73, 98, 86, },
		{"jiro", 64, 45, 40, },
		{"saburo", 76, 78, 69, },
	};

	int size = sizeof student / sizeof *student;   // "*student" eq "student[0]"

	for(int i = 0; i < size; i++){
		Show(student[i]);
	}
}
