CC=g++
CFLAGS=-O3 -std=c++11
EXEC=coloring
SOURCES=*.cpp

build:
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXEC)

test: $(EXEC)
	make build
	./coloring < testfall/yes.in | diff - testfall/yes.out


kattis:
	make test
	kattissubmit -p oldkattis:adkreduction1 $(SOURCES)


.PHONY: kattis build test
