CPP = g++ -Wall -Wconversion -Wfatal-errors -g -std=c++14 -fsanitize=undefined,address -O2

%: %.cpp
	$(CPP) -o$@ $<
