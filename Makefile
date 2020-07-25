CPP = g++ -Wall -Wconversion -Wfatal-errors -g -std=c++14 -fsanitize=undefined,address

target/%: src/%.cpp
	$(CPP) -o$@ $<
