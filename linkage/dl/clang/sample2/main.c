#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

void mainhoge ()
{
    printf("I'm hoge in main file\n");
}

int
main(int argc, char *argv[], char *environ[])
{
	void	*h;
	int	(*f) (int);
	
	// dlopenで共有ライブラリhello.soをロードします。
	h = dlopen ("./hello.so", RTLD_LAZY);
	if (h == NULL)
	{
		fprintf (stderr, "%s", dlerror() );
		exit (EXIT_FAILURE);
	}

    // dlsymで共有ライブラリのhello関数ポインタを取得します
	f = dlsym (h, "hello");

	if (f == NULL)
	{
		fprintf (stderr, "%s\n", dlerror() );
		exit (EXIT_FAILURE);
	}

    // dlsymで取得した関数ポインタを指定して実行する
	printf ("%d\n", (f) (200));

	// 不要になったライブラリを閉じる
	dlclose (h);

	exit (EXIT_SUCCESS);
}
