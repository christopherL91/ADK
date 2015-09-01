CC=g++
CFLAGS=-c -Wall -std=c++11 -O3
INDEXFILE=ut
EXECUTABLE=index
TOKENIZEREXEC=tokenizer

all: index

$(INDEXFILE): tokenizer.c korpus
	export LC_COLLATE=C
	cc ./tokenizer.c -o $(TOKENIZEREXEC)
	./$(TOKENIZEREXEC) < korpus | sort > $(INDEXFILE)

index: main.o gen_index.o $(INDEXFILE)
	$(CC) main.o gen_index.o -o $(EXECUTABLE)
	./$(EXECUTABLE) $(INDEXFILE)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

gen_index.o: gen_index.cpp
	$(CC) $(CFLAGS) gen_index.cpp

clean:
	rm -rf *.o $(EXECUTABLE) $(TOKENIZEREXEC)
	rm -rf *.idx

