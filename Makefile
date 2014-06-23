SOURCES=joshua.o main.o util.o chatbot.o games.o strings.o
HEADERS=chatbot.h games.h joshua.h location.h strings.h map.h util.h
CXXFLAGS=-I. -lncurses -g
CFLAGS=-I. -std=gnu99 -g
all: $(SOURCES) $(HEADERS)
	g++ $(SOURCES) -lncurses 
clean:
	rm -f $(SOURCES) a.out *~
