all: hellovalgrind hellovalgrindok

hellovalgrind: hellovalgrind.cc
	g++ $? -o ng

hellovalgrindok: hellovalgrindok.cc
	g++ $? -o ok

checkng:
	valgrind --leak-check=yes ./ng

checkok:
	valgrind --leak-check=yes ./ok

clean:
	rm -f ./a.out ./ng ./ok
