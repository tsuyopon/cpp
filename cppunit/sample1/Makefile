#
# Generic Makefile for C++
#
# Usage: Throw into your source directory and adjust the NAME variable.
#        NAME will be the name of the created binary.
#
NAME = test_runner

CXX = g++
CXXFLAGS = -Wall `cppunit-config --cflags`
LDFLAGS = `cppunit-config --libs`


#
# nothing to change down here
#

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))

.PHONY: test clean distclean


$(NAME): $(OBJ) 
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) 

test: $(NAME)
	@echo Running test suite ...
	@./$(NAME)

clean: 
	$(RM) $(NAME) $(OBJ)

distclean: clean
	$(RM) depend

depend:
	$(CXX) -MM $(CXXFLAGS) $(SRC) > depend

# Include dependencies, do not delete!
-include depend
