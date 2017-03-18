all: bin main
main: bin/main.o
	g++ -fprofile-arcs -ftest-coverage -g bin/main.o -o main
bin/main.o: src/main.cpp include/my_array.h 
	g++ -c -fprofile-arcs -ftest-coverage -std=c++03 -pedantic -Wall -Wextra -I ./include src/main.cpp -o bin/main.o
clean:
	rm -rf bin main
bin:
	mkdir -p bin
