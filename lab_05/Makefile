all: bin main
main: bin/main.o bin/clist.o bin/io.o
	gcc bin/main.o bin/clist.o bin/io.o -o main
bin/main.o: src/main.c include/clist.h include/io.h
	gcc -c -g -I ./include src/main.c -o bin/main.o
bin/clist.o: src/clist.c include/clist.h
	gcc -c -g -I ./include src/clist.c -o bin/clist.o
bin/io.o: src/io.c include/io.h include/clist.h
	gcc -c -g -I ./include src/io.c -o bin/io.o
clean:
	rm -f -r bin
	rm -f -r main
bin:
	mkdir -p bin
