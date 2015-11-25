
all:
	echo "Compilar desde CCS"

clean:
	rm -rf out	
	
test:
	mkdir -p uTests
	gcc -fprofile-arcs -ftest-coverage -fPIC -O0 test/test.c -o uTests/test
	./uTests/test
	
coverage:
	mkdir -p uTests out
	gcc -fprofile-arcs -ftest-coverage -fPIC -O0 test/test.c -o uTests/test
	./uTests/test
	gcovr -r . --xml-pretty -o out/coverage.xml
	rm -rf test.gcda test.gcno	
	
cppcheck:
	mkdir -p out
	cppcheck --xml --xml-version=2 --enable=all --inconclusive . 2> out/cppcheck.xml
	
doxygen:
	doxygen doc/Doxyfile 

count:
	mkdir -p out
	cloc --by-file --xml --out=out/cloc.xml .
