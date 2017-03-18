all: bin empl_db
empl_db: bin/main.o bin/employees.o
	g++ bin/main.o bin/employees.o -o empl_db
bin/main.o: src/main.cpp include/employees.h
	g++ -c -g -I ./include src/main.cpp -o bin/main.o
bin/employees.o: src/employees.cpp include/employees.h
	g++ -c -g -I ./include src/employees.cpp -o bin/employees.o
clean:
	rm -f -r bin
	rm -f -r empl_db
bin:
	mkdir -p bin
