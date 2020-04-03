#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define STACK_SIZE 1024*1024
static char child_stack[STACK_SIZE];

static int child_fn() {
  printf("Child PID: %ld\n", (long)getpid());      // 1 に見える
  printf("Parent PID: %ld\n", (long)getppid());    // 0 に見える
  return 0;
}

int main() {
// int clone(int (*fn)(void *), void *child_stack,
//           int flags, void *arg, ... 
//           /* pid_t *ptid, struct user_desc *tls, pid_t *ctid */ );

  // 通常、clone(2)のchild_stack引数は子プロセスのために用意したスタック(メモリ空間)の一番大きいアドレスを指定する。
  // (スタックはアドレスが小さい方向へと伸びるため)
  pid_t child_pid = clone(child_fn, child_stack+STACK_SIZE, CLONE_NEWPID | SIGCHLD, NULL);
  printf("clone() = %ld\n", (long)child_pid);
  printf("My PID: %ld\n", (long)getpid());
  waitpid(child_pid, NULL, 0);
  return 0;
}
