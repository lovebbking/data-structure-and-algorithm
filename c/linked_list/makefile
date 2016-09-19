test.out: main.o linked_list.o
	cc -o test.out main.o linked_list.o

test.o: main.c linked_list.h
	cc -c main.c

linked_list.o: linked_list.h linked_list.c
	cc -c linked_list.c
