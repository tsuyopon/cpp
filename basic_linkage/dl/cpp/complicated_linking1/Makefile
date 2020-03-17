# This file is part of the C++ dlopen mini HOWTO. You can find the complete
# HOWTO and/or updated versions at
# http://www.isotton.com/howtos/C++-dlopen-mini-HOWTO/
#
# Copyright 2002-2006 Aaron Isotton <aaron@isotton.com>
# Licensed under the GNU GPL.
#
all:
	gdb ./example1 -x test.gdbinit

example1: external.so hello.so hello2.so hello3.so 
	$(CXX) $(CXXFLAGS) -g -o example1 main.cpp -ldl

hello.so: hello.cpp
	$(CXX) $(CXXFLAGS) -g -export-dynamic -shared -o hello.so hello.cpp -fPIC

hello2.so: hello2.cpp
	$(CXX) $(CXXFLAGS) -g -export-dynamic -shared -o hello2.so hello2.cpp -fPIC -ldl -Wl,-rpath,'$$ORIGIN' -L. -lexternal

hello3.so: hello3.cpp
	$(CXX) $(CXXFLAGS) -g -export-dynamic -shared -o hello3.so hello3.cpp -fPIC 

external.so: external.cpp
	$(CXX) $(CXXFLAGS) -g -shared -o libexternal.so external.cpp -fPIC -Wl,-soname,libexternal.so

clean:
	rm -f example1 hello.so hello2.so hello3.so libexternal.so testlog.*

.PHONY: clean
