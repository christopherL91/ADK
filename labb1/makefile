CC=g++
CFLAGS=-c -Wall -std=c++11 -O3
EXECUTABLE=konkordans

all: Concordans

Concordans: main.o
	$(CC) main.o -o $(EXECUTABLE)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	-rm -rf *.o $(EXECUTABLE)
	-rm *.idx
