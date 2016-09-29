all: bin pos_db
pos_db: bin/main.o bin/clist.o
	gcc bin/main.o bin/clist.o -o pos_db
bin/main.o: src/main.c include/clist.h
	gcc -I ./include -c src/main.c -o bin/main.o
bin/clist.o: src/clist.c include/clist.h
	gcc -I ./include -c src/clist.c -o bin/clist.o
clean:
	rm -f -r bin
	rm -f -r pos_d 
bin:
	mkdir -p bin
