CC = gcc
MAKE=make

test: testlist.o intlist.o
	$(CC) -o $@ testlist.o intlist.o

testlist.o: intlist_test.c intlist.h
	$(CC) -c $< -o $@

intlist.o: intlist.c intlist.h
	$(CC) -c $< -o $@
