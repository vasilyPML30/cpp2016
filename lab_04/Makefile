all: bin ms_cli
ms_cli: bin/ms_cli.o bin/mergesort.o
	gcc -Wall -Wextra -Wshadow -g bin/ms_cli.o bin/mergesort.o -o ms_cli
bin/ms_cli.o: src/ms_cli.c include/mergesort.h
	gcc -Wall -Wextra -Wshadow -g -I ./include -c src/ms_cli.c -o bin/ms_cli.o
bin/mergesort.o: src/mergesort.c include/mergesort.h
	gcc -Wall -Wextra -Wshadow -g -I ./include -c src/mergesort.c -o bin/mergesort.o
clean:
	rm -f -r bin
	rm -f -r ms_cli
bin:
	mkdir -p bin
