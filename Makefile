CXXFLAGS := -std=c++17 -Wall -Wextra -Werror -fcompare-debug-second

test.out: test.cpp vecinsn.hpp
	g++ -O3 $(CXXFLAGS) $< -o $@
	./$@
	rm ./$@
