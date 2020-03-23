#include <stdio.h>
#include <dlfcn.h>

void	*h;
void (*f) (void);

int
hello (int i)
{
	printf ("Hello, %d\n", i);
	h = dlopen ("./subhello.so", RTLD_LAZY);
	f = dlsym (h, "subhello");
	(*f)();
	return (i + 1);
}


void 
goodbye (void)
{
	dlclose(h);
	printf ("Goodbye");
}

