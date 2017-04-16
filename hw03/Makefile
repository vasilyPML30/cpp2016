all: bin bin/huffman
bin/huffman: bin/main.o bin/huffman.o
	g++ bin/main.o bin/huffman.o -o bin/huffman
bin/main.o: src/main.cpp src/huffman.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g src/main.cpp -o bin/main.o
bin/huffman.o: src/huffman.cpp src/huffman.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g src/huffman.cpp -o bin/huffman.o
clean:
	rm -fr bin
bin:
	mkdir -p bin
