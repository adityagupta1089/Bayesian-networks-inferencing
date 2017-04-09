all:
	g++ ./src/*.cpp -I include -o bin/main.o
clean:
	rm -rf *.o *~
