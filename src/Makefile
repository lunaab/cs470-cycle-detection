CC = gcc --std=c99
MAKE=make

CLUSTER_LD=-L/shared/lib/igraph-0.7.1/build/lib
CLUSTER_C=-I/shared/lib/igraph-0.7.1/build/include/igraph

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

dist_detectors.o: dist_detectors.c dist_detectors.h graph.h graph.o intlist.o
	$(CC) -c $< -o $@ -pthread

dist_cycle_test: dist_cycle_test.o dist_detectors.o graph.o
	$(CC) -o $@ dist_cycle_test.o dist_detectors.o graph.o -pthread

dist_cycle_test.o: dist_cycle_test.c dist_detectors.h graph.h
	$(CC) -c $< -o $@ -pthread

cycle_test: cycle_test.o detectors.o intlist.o graph.o
	$(CC) -o $@ cycle_test.o detectors.o graph.o intlist.o

cycle_test.o: cycle_test.c detectors.h intlist.h graph.h
	$(CC) -c $< -o $@

bfs_cycle: bfs_cycle.c
	mpicc $< $(CLUSTER_C) $(CLUSTER_LD) -ligraph -lpthread -o $@

clean:
	rm *.o test
