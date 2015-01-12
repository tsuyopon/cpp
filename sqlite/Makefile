database:
	sqlite3 test.db "CREATE TABLE test(id integer, name text)"
	sqlite3 test.db ".import import.sql test"

connect_select: connect_select.cc
	g++ $? -lsqlite3 -o connect_select

clean:
	rm -f test.db connect_select
