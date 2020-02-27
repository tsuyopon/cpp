// char *hoge, hoge[], hoge[N]で初期化された場合のアドレス割当の違いを確認するプログラム
//
// 注意: コンパイル時にwarningが出てくるが、文字列を%pで出力しようとしてるだけなので無視してOK
#include<cstdio>

int main(){
	char *localVar = const_cast<char*>("Hoge");
	char localVarBraket[] = "Hoge";
	char localVarBraketInit[5] = "Hoge";

	// 文字列配列のアドレス宣言の場合には、localVarとlocalVar[0]のアドレスは異なる。つまり、アドレス(localVar)と実体を指すアドレス(&localVar[0])はそれぞれ別のメモリ上に存在する。
	// このパターンでは、localVarは高位に定義され、実体は低位アドレスに配置されるのが他と異なる。コンパイル後のバイナリをobjdump -x a.outして確認すると、この場合には.rodataセクションに実体が配置されることが確認できる。高位の場合にはスタックで配置される。
	printf("(1.1) localVar=%p\n", localVar);
	printf("(1.2) &localVar=%p\n", &localVar);
	printf("(1.3) localVar[0]=%p\n", localVar[0]);                        // これは文字列 "H" を表す
	printf("(1.4) &localVar[0]=%p\n\n", &localVar[0]);

	// 文字列配列の実体宣言の場合には、(2.1), (2.2), (2.4)は全て同じアドレスを表す。つまり、localVarアドレス(&localVarBraket)と実体を指すアドレス(&localVarBraket[0])は同一アドレス
	printf("(2.1) localVarBraket=%p\n", localVarBraket);          
	printf("(2.2) &localVarBraket=%p\n", &localVarBraket);
	printf("(2.3) localVarBraket[0]=%p\n", localVarBraket[0]);            // これは文字列 "H" を表す
	printf("(2.4) &localVarBraket[0]=%p\n\n", &localVarBraket[0]);

	printf("(3.1) localVarBraketInit=%p\n", localVarBraketInit);          
	printf("(3.2) &localVarBraketInit=%p\n", &localVarBraketInit);
	printf("(3.3) localVarBraketInit[0]=%p\n", localVarBraketInit[0]);    // これは文字列 "H" を表す
	printf("(3.4) &localVarBraketInit[0]=%p\n", &localVarBraketInit[0]);
}
