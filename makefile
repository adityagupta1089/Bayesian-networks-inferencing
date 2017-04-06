all:
	g++ ./src/main.cpp -I include -o bin/main.o
clean:
	rm -rf *.o *~