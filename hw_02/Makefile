all: bin main
board_test: bin bin/Board.o bin/Test.o bin/BoardTest.o bin/test.o
	g++ bin/Board.o bin/Test.o bin/BoardTest.o bin/test.o -o board_test
main: bin/main.o bin/Board.o bin/BoardView.o bin/NcursesView.o
	g++ bin/main.o bin/Board.o bin/BoardView.o bin/NcursesView.o -lncurses -o main
bin/NcursesView.o:  src/NcursesView.cpp include/Board.h include/NcursesView.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g -I ./include src/NcursesView.cpp -o bin/NcursesView.o
bin/test.o: test/BoardTest.cpp include/BoardTest.h test/Test.cpp include/Test.h test/test.cpp
	g++ -c -Wall -Wextra -Wshadow -Werror -g -I ./include test/test.cpp -o bin/test.o
bin/Test.o: test/Test.cpp include/Test.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g -I ./include test/Test.cpp -o bin/Test.o
bin/BoardTest.o: test/BoardTest.cpp include/BoardTest.h test/Test.cpp include/Test.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g -I ./include test/BoardTest.cpp -o bin/BoardTest.o
bin/main.o: src/main.cpp include/Board.h include/BoardView.h include/NcursesView.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g -I ./include src/main.cpp -o bin/main.o
bin/Board.o: src/Board.cpp include/Board.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g -I ./include src/Board.cpp -o bin/Board.o
bin/BoardView.o: src/BoardView.cpp include/Board.h include/BoardView.h
	g++ -c -Wall -Wextra -Wshadow -Werror -g -I ./include src/BoardView.cpp -o bin/BoardView.o
clean:
	rm -f -r bin
	rm -f -r main
	rm -f -r board_test
bin:
	mkdir -p bin
