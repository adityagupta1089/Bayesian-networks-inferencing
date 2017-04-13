IDIR=include
SDIR=src
ODIR=bin

CC=clang++
CFLAGS=-I$(IDIR) -std=c++11 -Wall -g

_DEPS = functions.hpp network.hpp queries.hpp
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

SOURCES = factors.cpp print.cpp queries.cpp read_write.cpp rejection_sampling.cpp variable_elimination.cpp 
_OBJ = $(SOURCES:.cpp=.o)
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

executable: $(OBJ)
	$(CC) -o $(ODIR)/main.o $(SDIR)/main.cpp $(OBJ) $(CFLAGS)
	
all: executable $(OBJ)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 