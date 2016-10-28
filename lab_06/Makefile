all: bin main
main: bin/main.o bin/phonebook.o
	gcc bin/main.o bin/phonebook.o -lexpat -o main
bin/main.o: src/main.c include/phonebook.h
	gcc -c -g -I ./include src/main.c -o bin/main.o
bin/phonebook.o: src/phonebook.c include/phonebook.h include/names.h
	gcc -c -g -I ./include src/phonebook.c -o bin/phonebook.o
clean:
	rm -f -r bin
	rm -f -r main
bin:
	mkdir -p bin
