all: bin str
str: bin/test.o bin/test_str.o bin/str.o
	gcc bin/test.o bin/test_str.o bin/str.o -o test
bin/test.o: src/test.c 
	gcc -I ./include -c src/test.c -o bin/test.o
bin/test_str.o: src/test_str.c include/test_str.h
	gcc -I ./include -c src/test_str.c -o bin/test_str.o
bin/str.o: src/str.c include/str.h
	gcc -I ./include -c src/str.c -o bin/str.o
clean:
	rm -f -r bin
	rm -f -r test
bin:
	mkdir -p bin
