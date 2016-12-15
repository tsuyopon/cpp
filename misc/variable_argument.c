#include <stdarg.h>
#include <stdio.h>

void vararg_func( int * sum , int argc , ... ) {
  va_list list;/* 定義するだけで値は設定しない */
  int i;

  *sum = 0;

  /* 1. 可変引数にアクセスする前の初期処理 */
  /* 第２引数に指定するargcは、vararg_func引数"..."の 直ぐ左側でなければならない*/
  va_start( list ,  argc );

  for( i=0 ; i<argc ; i++ ) {
    /* 2.可変引数にアクセスしてその変数を取り出す処理 */
    /* 第２引数にint型を固定指定 */
    *sum += va_arg( list , int );
  }

  /* 3. 可変引数にアクセスした後の終了処理 */
  va_end( list );
}

int main() {
  int sum;
  vararg_func( &sum , 3, 10, 20, 30); // 3は引数の数
  printf( "sum=%d\n" , sum );
  return 0;
}
