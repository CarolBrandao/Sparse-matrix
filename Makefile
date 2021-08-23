all:
	gcc -o main main.c sparse_matrix.c sparse_matrix.h -I.
	./main
