test.out: main.o sequence_list.o
	cc -o test.out main.o sequence_list.o

test.o: main.c sequence_list.h
	cc -c main.c

sequence_list.o: sequence_list.h sequence_list.c
	cc -c sequence_list.c
