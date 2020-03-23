#include <stdio.h>
#include <sqlite3.h>

void subhello (void)
{
	printf ("subhello\n");
	sqlite3 *conn = NULL;
        int ret       = 0;
        ret = sqlite3_open(
          "./db_test.sqlite3" , // DBファイル名
          &conn                 // DBコネクション
        );
}
