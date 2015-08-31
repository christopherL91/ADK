sl : sl.o main.o
	gcc -Wall -o sl sl.o main.o

sl.o : sl.c skiplist.h
	gcc -Wall -g -c sl.c

main.o : main.c skiplist.h
	gcc -Wall -g -c main.c
