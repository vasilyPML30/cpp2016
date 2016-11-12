all: bin main
main: bin/main.o bin/bmp.o bin/message.o
	gcc bin/main.o bin/bmp.o bin/message.o -o main
bin/main.o: src/main.c include/bmp.h include/message.h
	gcc -c -std=c99 -Wall -Wextra -Wshadow -Werror -g -I ./include src/main.c -o bin/main.o
bin/message.o: src/message.c include/bmp.h include/message.h
	gcc -c -std=c99 -Wall -Wextra -Wshadow -Werror -g -I ./include src/message.c -o bin/message.o
bin/bmp.o: src/bmp.c include/bmp.h
	gcc -c -std=c99 -Wall -Wextra -Wshadow -Werror -g -I ./include src/bmp.c -o bin/bmp.o
clean:
	rm -f -r bin
	rm -f -r main
bin:
	mkdir -p bin
