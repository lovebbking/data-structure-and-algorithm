test.out: main.o stack.o
	cc -o test.out main.o stack.o

test.o: main.c stack.h
	cc -c main.c

stack.o: stack.h stack.c
	cc -c stack.c
