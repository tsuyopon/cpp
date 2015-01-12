#include<iostream>
#include<cstdio>
#include<cstdlib>  // exit()
#include<sqlite3.h>

#define DBFILE "test.db"
using namespace std;

static int callBack(void *arg, int argc, char **argv, char **column){
	int i;
	for(i = 0; i < argc; i++){
		printf("%s = %s\n", column[i], argv[i]);
	}
	return SQLITE_OK;
}

int main()
{
	sqlite3* dbp = NULL;
	char* err_msg = NULL;
	int rc = sqlite3_open(DBFILE, &dbp);
	if(SQLITE_OK != rc){
		cout << "Could not open sqlite" << endl;
		sqlite3_errmsg(dbp);
		exit(1);
	}

	rc = sqlite3_exec(dbp, "SELECT * FROM test WHERE id > 2;", callBack, NULL, &err_msg);
	if(SQLITE_OK != rc){
		cout << "Could not exec sqlite. errMsg=" << err_msg << endl;
		sqlite3_free(err_msg);
		sqlite3_close(dbp);
		exit(1);
	}
	sqlite3_close(dbp);
	dbp = NULL;

}
