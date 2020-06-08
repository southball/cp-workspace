CPP = g++ -Wall -Wconversion -Wfatal-errors -g -std=c++14 -fsanitize=undefined,address

%: %.cpp snippets.cpp
	./preprocessor $@.cpp > /tmp/$@.proc.cpp
	$(CPP) -O2 -o$@ /tmp/$@.proc.cpp

preprocessor: preprocessor.cpp
	$(CPP) -o$@ $<
