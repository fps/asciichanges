CXXFLAGS="-I."

tests/001: tests/001.cc
	$(CXX) $(CXXFLAGS) -o tests/001 tests/001.cc
