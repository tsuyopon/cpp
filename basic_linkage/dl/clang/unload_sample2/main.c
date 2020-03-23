#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

int
main(int argc, char *argv[], char *environ[])
{
        // for hello (hello.so)
	void	*h;
	int	(*f) (int);
	void (*f_2) (void);

        // for greeding (greeding.so)
	void	*h2;
	void (*f2) (void);
	
////////////////////////////////////////////////////////////
// helloの呼び出し(helloからはdlopenでsubhelloが呼ばれる)
////////////////////////////////////////////////////////////
	// dlopenで共有ライブラリhello.soをロードします。
	h = dlopen ("./hello.so", RTLD_LAZY);
	if (h == NULL)
	{
		fprintf (stderr, "%s", dlerror() );
		exit (EXIT_FAILURE);
	}
        // dlsymで共有ライブラリのhello関数ポインタを取得します
	f = dlsym (h, "hello");
	f_2 = dlsym (h, "goodbye");

	if (f == NULL || f_2 == NULL) {
		fprintf (stderr, "%s\n", dlerror() );
		exit (EXIT_FAILURE);
	}

        // dlsymで取得した関数ポインタを指定して実行する
	printf ("From main: %d\n", (f) (200));

////////////////////////////////////////////////////////////
// greedingsの呼び出し
////////////////////////////////////////////////////////////
	// dlopenで共有ライブラリgreeding.soをロードします。
	h2 = dlopen ("./greeding.so", RTLD_LAZY);
	if (h2 == NULL)
	{
		fprintf (stderr, "%s", dlerror() );
		exit (EXIT_FAILURE);
	}

        // dlsymで共有ライブラリのhello関数ポインタを取得します
	f2 = dlsym (h2, "greeding");
	if (f2 == NULL)
	{
		fprintf (stderr, "%s\n", dlerror() );
		exit (EXIT_FAILURE);
	}


	(*f)(1);
	(*f_2)();

////////////////////////////////////////////////////////////
// greedingの呼び出しとgreeding.soのクローズ
////////////////////////////////////////////////////////////
	(*f2)();
	dlclose (h2);

////////////////////////////////////////////////////////////
// hello.soのクローズ
////////////////////////////////////////////////////////////
	// 不要になったライブラリを閉じる
	dlclose (h);



       
	exit (EXIT_SUCCESS);
}
