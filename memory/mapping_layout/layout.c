/*
 * 参考: http://th0x4c.github.io/blog/2012/10/10/os-virtual-memory-map/
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>

#define STRSIZE 64

void hello(char *name);
void hello_local_world();

char not_initialized_global_world[STRSIZE];
char initialized_global_world[STRSIZE] = "initialized global world";


int main(int argc, char *argv[])
{
  static char not_initialized_static_world[STRSIZE];
  static char initialized_static_world[STRSIZE] = "initialized static world";
  char *malloc_world;
  int shmid;
  char *shared_memory_world;
  char *big_malloc_world;
  char *medium_malloc_world_1;
  char *medium_malloc_world_2;

  strcpy(not_initialized_global_world, "not initialized global world");

  strcpy(not_initialized_static_world, "not initialized static world");

  malloc_world = (char *) malloc(sizeof(char) * STRSIZE);
  strcpy(malloc_world, "malloc world");

  shmid = shmget(IPC_PRIVATE, sizeof(char) * STRSIZE, 0666 | IPC_CREAT);
  shared_memory_world = (char *) shmat(shmid, 0, 0);
  strcpy(shared_memory_world, "shared memory world");

  big_malloc_world = (char *) malloc(256 * 1024);
  strcpy(big_malloc_world, "big malloc world");

  medium_malloc_world_1 = (char *) malloc(131 * 1024 + 905);
  strcpy(medium_malloc_world_1, "medium malloc world 1");

  medium_malloc_world_2 = (char *) malloc(131 * 1024 + 904);
  strcpy(medium_malloc_world_2, "medium malloc world 2");

  hello(argv[1]);
  hello(not_initialized_global_world);
  hello(initialized_global_world);
  hello(not_initialized_static_world);
  hello(initialized_static_world);
  hello(malloc_world);
  hello(shared_memory_world);
  hello(big_malloc_world);
  hello(medium_malloc_world_1);
  hello(medium_malloc_world_2);
  hello_local_world();

  getchar();

  free(malloc_world);
  shmdt(shared_memory_world);
  shmctl(shmid, IPC_RMID, 0);
  free(big_malloc_world);
  free(medium_malloc_world_1);
  free(medium_malloc_world_2);

  return 0;
}

void hello(char *name)
{
  printf("hello, %s: 0x%016lx\n", name, name);
}

void hello_local_world()
{
  char local_world[STRSIZE];

  strcpy(local_world, "local world");
  hello(local_world);
}

