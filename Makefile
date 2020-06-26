CPP = g++ -Wall -Wconversion -Wfatal-errors -g -std=c++14 -fsanitize=undefined,address

%: %.cpp snippets.cpp
	./preprocessor $@.cpp > ./$@.proc.cpp
	$(CPP) -o$@ ./$@.proc.cpp

preprocessor: preprocessor.cpp
	$(CPP) -o$@ $<
