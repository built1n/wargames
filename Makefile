SOURCES=joshua.o main.o
CXXFLAGS=-I. -lncurses
CFLAGS=-I. -std=gnu99
all: $(SOURCES)
	g++ $(SOURCES) -lncurses 
