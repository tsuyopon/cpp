#include <stdio.h>
#include <pthread.h>

__thread   int a = 0;
           int b = 0;

void *func(void *arg)
{
   a++;
   b++;
   printf("a = %d b=%d\n", a, b);
}

int main()
{
   pthread_t tid0, tid1;

   pthread_create(&tid0, NULL, func, NULL);
   pthread_create(&tid1, NULL, func, NULL);
   pthread_join(tid0, NULL);
   pthread_join(tid1, NULL);
}
