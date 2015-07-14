CXXFLAGS=-I. -std=c++11

tests/001: tests/001.cc asciichanges/asciichanges.h
	$(CXX) $(CXXFLAGS) -o tests/001 tests/001.cc
