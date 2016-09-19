test.out: main.o tree.o
	cc -o test.out main.o tree.o

test.o: main.c tree.h
	cc -c main.c

tree.o: tree.h tree.c
	cc -c tree.c
