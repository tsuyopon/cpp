#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>

char * alloc_workbuf(int size) {
 char *ptr;

 /* allocate some memory */
 ptr = malloc(size);

 /* return NULL on failure */
 if (ptr == NULL)
  return NULL;

 /* lock this buffer into RAM */
 if (mlock(ptr, size)) {
  free(ptr);
  return NULL;
 }
 return ptr;
}

void free_workbuf(char *ptr, int size) {
 /* unlock the address range */
 munlock(ptr, size);

 /* free the memory */
 free(ptr);
}

int main(){
	char *ptr;
	ptr = alloc_workbuf(10);
	free_workbuf(ptr, 10);
}
