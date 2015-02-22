//多重間接参照
#include<stdio.h>

int main(){
	const char *titles[] = {
		"A Tale of Two Cites",
		"Wuthering Heights",
		"Don Quixote",
		"Odyssey",
		"Mody-Dick",
		"Hamlet",
		"Gulliver's Travels" };
	
	const char **bestBooks[3];
	const char **englishBooks[4];

    // ベストセラーの本とタイトルを紐づける
	bestBooks[0] = &titles[0];
	bestBooks[1] = &titles[3];
	bestBooks[2] = &titles[5];

    // 英語の本とタイトルを紐づける
	englishBooks[0] = &titles[0];
	englishBooks[1] = &titles[1];
	englishBooks[2] = &titles[5];
	englishBooks[3] = &titles[6];

    // ２つだけ抽出して出力する
	printf("%s\n", *bestBooks[1]);
	printf("%s\n", *englishBooks[1]);

}
