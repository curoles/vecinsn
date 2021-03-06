CXXFLAGS := -std=c++17 -Wall -Wextra -Werror
CXXFLAGS += -finline-functions -fcompare-debug-second
CXXFLAGS += -march=native #-msse4.1

SRC := vx/vxtypes.hpp vx/vxops.hpp vx/vxadvops.hpp vx/vxarray.hpp
SRC += vx/vxcomplex.hpp

test.out: test/test_basic.cpp $(SRC)
	g++ -O3 $(CXXFLAGS) -I. $< -o $@
	./$@
	rm ./$@

# apt install texlive-latex-extra
#.PHONY: doc
#doc:
#	doxygen Doxyfile
#	cd ./latex && make
#	cp ./latex/refman.pdf README.pdf
#	rm -rf ./latex
