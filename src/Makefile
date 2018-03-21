CC = gcc
MAKE=make

test: testlist.o intlist.o
	$(CC) -o $@ testlist.o intlist.o

testlist.o: intlist_test.c intlist.h
	$(CC) -c $< -o $@

intlist.o: intlist.c intlist.h
	$(CC) -c $< -o $@

graph.o: graph.c graph.h
	$(CC) -c $< -o $@

detectors.o: detectors.c detectors.h graph.h graph.o intlist.o
	$(CC) -c $< -o $@

cycle_test: cycle_test.o detectors.o intlist.o graph.o
	$(CC) -o $@ cycle_test.o detectors.o graph.o intlist.o

cycle_test.o: cycle_test.c detectors.h intlist.h graph.h
	$(CC) -c $< -o $@

clean:
	rm *.o test
