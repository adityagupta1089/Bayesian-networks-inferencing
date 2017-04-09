all:
	clang++ -std=c++11 ./src/*.cpp -I include -o bin/main.o
clean:
	rm -rf *.o *~
