SOURCES=joshua.o main.o util.o chatbot.o gtnw.o strings.o
HEADERS=chatbot.h gtnw.h joshua.h location.h strings.h map.h util.h
CXXFLAGS=-I. -lncurses -g -O3
CFLAGS=-I. -std=gnu99 -g -O3
wargames: $(SOURCES) $(HEADERS)
	g++ $(SOURCES) $(CXXFLAGS) -lncurses -o wargames
all: wargames Makefile
clean:
	rm -f $(SOURCES) a.out wargames *~
