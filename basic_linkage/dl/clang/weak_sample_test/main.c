#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

int
main(int argc, char *argv[], char *environ[])
{
	void	*h1, *h2, *h3;
	void (*f1) (void);
	void (*f2) (void);
	void (*f3) (void);
	
	// hello.so (helloが定義される)
	h1 = dlopen ("./hello.so", RTLD_NOW|RTLD_GLOBAL);
	f1 = dlsym (h1, "hello");
	(*f1)();
	printf("f1:%p\n", f1);
	dlclose (h1);

	// hello2.so (weakでhelloが定義される)
	h2 = dlopen ("./hello2.so", RTLD_LAZY|RTLD_GLOBAL);   // RTLD_NOWにするとセグフォになる。なんで?
	f2 = dlsym (h2, "hello");
	(*f2)();
	printf("f2:%p\n", f2);

	// hello.so (helloが定義される)
	h3 = dlopen ("./hello.so", RTLD_NOW|RTLD_GLOBAL);
	f3 = dlsym (h3, "hello");
	(*f3)();
	printf("f3:%p\n", f3);


	dlclose (h2);
	dlclose (h3);

	exit (EXIT_SUCCESS);
}
