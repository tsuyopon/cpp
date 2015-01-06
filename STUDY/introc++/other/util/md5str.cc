#include <iostream>
#include <string>
#include <openssl/md5.h>

int main(){
}

class Util {
	public:
		static std::string md5str(const char* str){
			std::string md5String = "";
			unsigned char md5[MD5_DIGEST_LENGTH + 1];

			MD5( (unsigned char*)str, strlen(str), md5);
			for(int i = 0; i < MD5_DIGEST_LENGTH; i++){
				char hex[3];
				sprintf(hex, "%02x", md5[i]);
				md5String +=hex;
			}
			return md5String;
		}
};
