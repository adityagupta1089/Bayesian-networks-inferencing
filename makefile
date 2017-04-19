IDIR=include
SDIR=src
ODIR=bin
DDIR=debug

CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -Wall -Wextra -pedantic -O2
DCFLAGS=-I$(IDIR) -std=c++11 -Wall -Wextra -pedantic -g -DDEBUG=true

_DEPS = read_write.hpp network.hpp queries.hpp
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

SOURCES = factors.cpp print.cpp queries.cpp read_write.cpp rejection_sampling.cpp variable_elimination.cpp
_OBJ = $(SOURCES:.cpp=.o)
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))
DOBJ = $(patsubst %, $(DDIR)/%, $(_OBJ))


$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(DDIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(DCFLAGS)

release: $(OBJ)
	$(CC) -o $(ODIR)/main.o $(SDIR)/main.cpp $(OBJ) $(CFLAGS)

debug: $(DOBJ)
	$(CC) -o $(DDIR)/main.o $(SDIR)/main.cpp $(DOBJ) $(DCFLAGS)

all:
	mkdir -p $(ODIR)
	mkdir -p $(DDIR)
	make release
	make debug

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(DDIR)/*.o *~ core $(INCDIR)/*~ $(SDIR)/*~
