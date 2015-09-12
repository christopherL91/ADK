CC=g++
CFLAGS=-c -Wall -std=c++11 -O3
EXECUTABLE=match

all: match

match: main.o biparte.o
	$(CC) main.o biparte.o -o $(EXECUTABLE)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

biparte.o: biparte.cpp
	$(CC) $(CFLAGS) biparte.cpp

clean:
	rm -rf *.o $(EXECUTABLE)
