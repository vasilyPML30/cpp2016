all: bin main 
main: bin/main.o bin/product.o
	g++ bin/product.o bin/main.o -o main
bin/main.o: src/main.cpp include/my_vector.h include/my_vector_impl.h include/tests.h
	g++ -c -g -I ./include src/main.cpp -o bin/main.o
bin/product.o: src/product.cpp include/product.h 
	g++ -c -g -I ./include src/product.cpp -o bin/product.o
clean:
	rm -rf bin main
bin:
	mkdir -p bin
