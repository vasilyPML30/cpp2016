all: create lab1
lab1: bin/main.o bin/io.o bin/algorithm.o bin/util.o
	gcc bin/main.o bin/io.o bin/algorithm.o bin/util.o -o lab1
bin/main.o: src/main.c 
	gcc -I ./include -c src/main.c -o bin/main.o
bin/io.o: src/io.c include/io.h
	gcc -I ./include -c src/io.c -o bin/io.o
bin/algorithm.o: src/algorithm.c include/algorithm.h
	gcc -I ./include -c src/algorithm.c -o bin/algorithm.o
bin/util.o: src/util.c include/util.h
	gcc -I ./include -c src/util.c -o bin/util.o
clean:
	rm -f -r bin
	rm -f -r lab1
create:
	mkdir -p bin
