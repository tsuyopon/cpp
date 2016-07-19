#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

int
main(int argc, char *argv[], char *environ[])
{
	void	*h1, *h2;
	int	(*f1) (int);
	int	(*f2) (int);
	
	//////////////////////////////
	// hello.cの読み込み(dlopen, dlsym)
	//////////////////////////////
#ifndef RTLDGLOBAL
	// デフォルトはRTLD_LOCALが指定されているのと同じで、あとでの読み込み時にシンボルが参照できなくなる
	h1 = dlopen ("./hello.so", RTLD_LAZY);
#else
	// RTLD_GLOBALを付与すると、あとで読み込まれたライブラリ
	h1 = dlopen ("./hello.so", RTLD_LAZY|RTLD_GLOBAL);
#endif
	if (h1 == NULL) {
		fprintf (stderr, "%s", dlerror() );
		exit (EXIT_FAILURE);
	}

	f1 = dlsym (h1, "hello");
	if (f1 == NULL) {
		fprintf (stderr, "%s\n", dlerror() );
		exit (EXIT_FAILURE);
	}

	printf ("%d\n", (f1) (200));

	//////////////////////////////
	// ここからhello2.cの読み込み
	//////////////////////////////
	h2 = dlopen ("./hello2.so", RTLD_LAZY);
	if (h2 == NULL) {
		fprintf (stderr, "%s", dlerror() );
		exit (EXIT_FAILURE);
	}

	f2 = dlsym (h2, "hello2");
	if (f2 == NULL) {
		fprintf (stderr, "%s\n", dlerror() );
		exit (EXIT_FAILURE);
	}

    // dlsymで取得した関数ポインタを指定して実行する  ### この関数(hello2)の中では、hello.so側の関数を実行していることに注意
	printf ("%d\n", (f2) (200));

	dlclose (h2);
	dlclose (h1);

	exit (EXIT_SUCCESS);
}
