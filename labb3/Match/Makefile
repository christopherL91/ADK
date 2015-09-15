CC=g++
CFLAGS=-c -Wall -std=c++11 -O3
EXECUTABLE=match

all: match
maxflow: maxflow.o
	$(CC) -o maxflow maxflow.o

match: main.o biparte.o
	$(CC) main.o biparte.o -o $(EXECUTABLE)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

biparte.o: biparte.cpp
	$(CC) $(CFLAGS) biparte.cpp

maxflow.o: maxflow.cpp
	$(CC) $(CFLAGS) maxflow.cpp

clean:
	rm -rf *.o $(EXECUTABLE)
