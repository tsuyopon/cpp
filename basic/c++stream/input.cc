#include<iostream>
using namespace std;

int main()
{

	/* 入力 */
	cout << "Input Your Name: " << flush;          /* ここで「Azarashi Taro」と入力すると正しく認識せず単語として読み込みます */
	char yourname[100];                            // 型宣言が文頭以外でもできることに着目
	cin >> yourname;

	cout << "Input Your Age: " << flush;
	int age;
	cin >> age;

	/* 結果の出力 */
	cout << "Results: " << endl;
	cout << "\tName: "  << yourname << endl;
	cout << "\tAge:  "  << age      << endl;
}
