.PHONY: all

all: tests/001 tests/002

CXXFLAGS=-I. -std=c++11

tests/001: tests/001.cc asciichanges/asciichanges.h asciichanges/chords.h
	$(CXX) $(CXXFLAGS) -o tests/001 tests/001.cc

tests/002: tests/002.cc asciichanges/asciichanges.h asciichanges/chords.h
	$(CXX) $(CXXFLAGS) -o tests/002 tests/002.cc
