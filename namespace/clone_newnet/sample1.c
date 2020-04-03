#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define STACK_SIZE 1024*1024
static char child_stack[STACK_SIZE];

static int child_fn() {
  printf("New `net` Namespace:\n");
  system("ip link");
  printf("\n\n");
  return 0;
}

int main() {
  printf("Original `net` Namespace:\n");
  system("ip link");
  printf("\n\n");
  // CLONE_NEWNETを入れた場合と、入れな場合で出力結果を比較してみると良いでしょう。
  pid_t child_pid = clone(child_fn, child_stack+STACK_SIZE, CLONE_NEWPID | CLONE_NEWNET | SIGCHLD, NULL);
  waitpid(child_pid, NULL, 0);
  return 0;
}
