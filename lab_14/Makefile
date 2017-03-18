all: bin main
main: bin/main.o bin/matrix.o
	g++ -g bin/main.o bin/matrix.o -o main
bin/main.o: src/main.cpp include/matrix.h 
	g++ -c -std=c++03 -pedantic -Wall -Wextra -I ./include src/main.cpp -o bin/main.o
bin/matrix.o: src/matrix.cpp include/matrix.h 
	g++ -c -std=c++03 -pedantic -Wall -Wextra -I ./include src/matrix.cpp -o bin/matrix.o
clean:
	rm -rf bin main
bin:
	mkdir -p bin
