CPP = g++ -Wall -Wconversion -Wfatal-errors -g -std=c++14 -fsanitize=undefined,address

%: %.cpp
	$(CPP) -o$@ $<
