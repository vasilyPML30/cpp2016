all: bin huffman
huffman: bin/main.o bin/huffman.o bin/bitstream.o
	g++ bin/main.o bin/huffman.o bin/bitstream.o -o huffman
bin/main.o: src/main.cpp src/huffman.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g src/main.cpp -o bin/main.o
bin/huffman.o: src/huffman.cpp src/huffman.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g src/huffman.cpp -o bin/huffman.o
bin/bitstream.o: src/bitstream.cpp src/bitstream.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g src/bitstream.cpp -o bin/bitstream.o
clean:
	rm -fr bin huffman
bin:
	mkdir -p bin
