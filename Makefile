CXXFLAGS := -std=c++17 -Wall -Wextra -Werror
CXXFLAGS += -finline-functions -fcompare-debug-second
CXXFLAGS += -msse4.1

test.out: test.cpp vecinsn.hpp
	g++ -O3 $(CXXFLAGS) $< -o $@
	./$@
	rm ./$@
