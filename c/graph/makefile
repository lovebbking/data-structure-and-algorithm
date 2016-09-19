test.out: main.o graph.o
	cc -o test.out main.o graph.o

test.o: main.c graph.h
	cc -c main.c

graph.o: graph.h graph.c
	cc -c graph.c
