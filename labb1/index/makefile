CC=g++
CFLAGS=-c -Wall -std=c++11 -O3
ADK_PATH=../adk14/labb1
INDEXFILE=ut
EXECUTABLE=index
TOKENIZEREXEC=tokenizer

all: index

file: tokenizer.c
	export LC_COLLATE=C
	cc $(ADK_PATH)/tokenizer.c -o $(TOKENIZEREXEC)
	$(TOKENIZEREXEC) < $(ADK_PATH)/korpus | sort > ./$(INDEXFILE)

index: main.o gen_index.o
	$(CC) main.o gen_index.o -o $(EXECUTABLE)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

gen_index.o: gen_index.cpp
	$(CC) $(CFLAGS) gen_index.cpp

clean:
	rm -rf *.o $(EXECUTABLE) $(TOKENIZEREXEC)
	rm -rf *.idx

