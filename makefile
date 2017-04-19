IDIR=include
SDIR=src
ODIR=bin

CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -Wall -Wextra -pedantic -O2

_DEPS = read_write.hpp network.hpp queries.hpp
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

SOURCES = factors.cpp print.cpp queries.cpp read_write.cpp rejection_sampling.cpp variable_elimination.cpp
_OBJ = $(SOURCES:.cpp=.o)
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

release: $(OBJ)
	$(CC) -o $(ODIR)/main.o $(SDIR)/main.cpp $(OBJ) $(CFLAGS)

all: release

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(SDIR)/*~
