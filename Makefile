CPP = g++ -Wall -Wconversion -Wfatal-errors -g -std=c++14 -fsanitize=undefined,address

all: target/a target/b target/c target/d target/e target/f

proc/%.cpp: src/%.cpp snippets.cpp target/preprocessor
	./target/preprocessor $< ./snippets.cpp > $@

target/%: proc/%.cpp
	$(CPP) -o$@ $<

target/preprocessor: tools/preprocessor.cpp
	$(CPP) -o$@ $<
