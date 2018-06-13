CC=g++
CFLAGS=-std=c++0x -g
SRCS=main.cpp Jumbo.cpp
EXEC=Jumbo

all: $(SOURCES)
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC)

clean: 
	rm Jumbo *~ 
