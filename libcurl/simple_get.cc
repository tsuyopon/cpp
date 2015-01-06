/*
 * This program is curl sample.
 * Get simple url and write data into textfile(test.txt).
 * <usage>  $ ./a.out
 *
 */
#include<curl/curl.h>
#include<stdio.h>

int main(int argc, char *argv[]){
	CURL *curl;
	CURLcode res;
	char *str = (char*)"test.txt";

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "http://www.yahoo.co.jp/");
	FILE *fp = fopen(str, "w");
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	res = curl_easy_perform(curl);

	long http_code = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
	curl_easy_cleanup(curl);
	fclose(fp);
	printf("write %s\n", str);
	return 0;
}
