CC=g++
STD=-std=c++11

#Graph
Graph: Graph.o
	$(CC) $(STD) -o $@ $^

clean:
	rm -f Graph *.o
