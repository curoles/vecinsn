CXXFLAGS := -std=c++17 -Wall -Wextra -Werror
CXXFLAGS += -finline-functions -fcompare-debug-second
CXXFLAGS += -march=native #-msse4.1

SRC = vxtypes.hpp vxops.hpp vxarray.hpp

test.out: test.cpp $(SRC)
	g++ -O3 $(CXXFLAGS) $< -o $@
	./$@
	rm ./$@

# apt install texlive-latex-extra
.PHONY: doc
doc:
	doxygen Doxyfile
	cd ./latex && make
	cp ./latex/refman.pdf README.pdf
	rm -rf ./latex
