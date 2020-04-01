#
# Generic Makefile for C++
#
# Usage: Throw into your source directory and adjust the NAME variable.
#        NAME will be the name of the created binary.
#
NAME = test_runner

CXX = g++

CXXFLAGS = -fprofile-arcs -ftest-coverage -Wall `cppunit-config --cflags`

# "-lgcov -coverage"が無いとリンクに失敗します。
# 参考: https://stackoverflow.com/questions/16682606/how-to-resolve-gcov-init-undefined-reference-issue-when-linking
LDFLAGS = -lgcov -coverage `cppunit-config --libs`

LCOV_INFO = lcov.info
COV_DIR = html

#
# nothing to change down here
#

BASE_SRC = ../Hoge.cc

# カレントディレクトリ中の.ccはwildcardから取得
SRC = $(BASE_SRC) $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))

.PHONY: test cov clean distclean


$(NAME): $(OBJ) 
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) 

test: $(NAME)
	@echo Running test suite ...
	@./$(NAME)

cov:
	lcov --directory . --capture --output $(LCOV_INFO)
	genhtml -o $(COV_DIR) $(LCOV_INFO)

clean:  
	$(RM) $(NAME) $(OBJ) *.gcov *.gcno *.gcda $(LCOV_INFO)
	$(RM) -r $(COV_DIR)

distclean: clean
	$(RM) depend

depend:
	$(CXX) -MM $(CXXFLAGS) $(SRC) > depend

# Include dependencies, do not delete!
-include depend
