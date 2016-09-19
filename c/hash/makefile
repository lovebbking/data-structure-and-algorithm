test.out: main.o hash.o
	cc -o test.out main.o hash.o

test.o: main.c hash.h
	cc -c main.c

hash.o: hash.h hash.c
	cc -c hash.c
