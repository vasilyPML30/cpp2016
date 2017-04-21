all: bin huffman
test: bin bin/autotest.o bin/test.o bin/huffman_test.o bin/huffman.o bin/bitstream.o
	g++ bin/autotest.o bin/huffman_test.o bin/huffman.o bin/bitstream.o bin/test.o -o bin/huffman
huffman: bin/main.o bin/huffman.o bin/bitstream.o
	g++ bin/main.o bin/huffman.o bin/bitstream.o -o bin/huffman
bin/main.o: src/main.cpp src/huffman.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g src/main.cpp -o bin/main.o
bin/huffman.o: src/huffman.cpp src/huffman.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g src/huffman.cpp -o bin/huffman.o
bin/bitstream.o: src/bitstream.cpp src/bitstream.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g src/bitstream.cpp -o bin/bitstream.o
bin/autotest.o: test/autotest.cpp test/autotest.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g test/autotest.cpp -o bin/autotest.o
bin/huffman_test.o: test/huffman_test.cpp test/huffman_test.h test/autotest.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g test/huffman_test.cpp -o bin/huffman_test.o
bin/test.o: test/test.cpp test/huffman_test.h test/autotest.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g test/test.cpp -o bin/test.o
clean:
	rm -fr bin huffman
bin:
	mkdir -p bin
