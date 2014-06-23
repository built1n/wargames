SOURCES=joshua.o main.o util.o chatbot.o games.o strings.o
CXXFLAGS=-I. -lncurses -g
CFLAGS=-I. -std=gnu99 -g
all: $(SOURCES)
	g++ $(SOURCES) -lncurses 
clean:
	rm -f $(SOURCES) a.out *~
