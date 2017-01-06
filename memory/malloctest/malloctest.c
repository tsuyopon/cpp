/*
 * mallocの動作を確認する
 *  文字の入力を受け付ける前にmallocで128KB未満(heap)か128KB以上(mmap)かの出しわけ処理を行う
 *
 * (1) heapを使う確認をする場合
 * $ make heap
 * $ ./useheap
 * 別のターミナルから
 * $ sudo cat /proc/`pidof useheap`/maps
 * [heap]が**ある**ことが確認できる
 *
 * (2) mmapを使う確認をする場合
 * $ make mmap
 * $ ./usemmap
 * 別のターミナルから
 * $ sudo cat /proc/`pidof usemmap`/maps
 * [heap]が**ない**ことが確認できる
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
   char *str;

   /* 文字列のためのメモリを確保 */
   // Linuxのmallocだと128KB未満ではHeapから割り当てを行い、128KB以上だとmmapを使用する。
#ifdef USEHEAP
   str = (char *)malloc(128*(1024-1));
#else
   str = (char *)malloc(128*1024);
#endif
   if(str == NULL) {
      printf("メモリが確保できません\n");
      exit(EXIT_FAILURE);
   }

   /* 文字列を入力 */
   gets(str);

   /* 文字列の表示 */
   puts(str);

   /* メモリの解放 */
   free(str);

   return 0;
}
