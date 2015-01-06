// curl callback version
#include<iostream>
#include<typeinfo>
#include "curl/curl.h"

using namespace std;

string getCurlRequest(char *url);
static size_t curlCallBack(char* buffer, size_t size, size_t nitems, void *outstream);

int main(){
	string body;
	try {
		char* url = (char*)"http://www.yahoo.co.jp";
		body = getCurlRequest(url);
		cout << body << endl;
	} catch(exception &e){
		cerr << e.what() << endl;
		cerr << typeid(e).name() << endl;
	}
	return 0;
}

string getCurlRequest(char* url){
	CURL *curl;
	CURLcode res;
	string resdata;

	curl = curl_easy_init();
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallBack);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (string*)&resdata);     // outstream [curlCallBack method]
		res = curl_easy_perform(curl);

		if(CURLE_OK != res){
			curl_easy_cleanup(curl);
			return 0;
		}
		curl_easy_cleanup(curl);
	}
	return resdata;
}

static size_t curlCallBack(char* buffer, size_t size, size_t nitems, void *outstream){
	int realsize = size * nitems;        // Body Bytes Size
	string *chunk = (string*)outstream;  // Body Data Responce Code
	(*chunk).append(buffer,realsize);    // Get <realsize> Bytes from <buffer>
	return realsize;
}
