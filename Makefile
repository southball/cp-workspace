CPP = g++ -Wall -Wconversion -Wfatal-errors -g -std=c++14 -fsanitize=undefined,address -I ./src/template

target/%: src/%.cpp $(wildcard src/template/*.h) $(wildcard src/template/**/*.h)
	$(CPP) -o$@ $<

tools/preprocessor: tools/preprocessor.rs
	rustc +nightly -otools/preprocessor tools/preprocessor.rs
