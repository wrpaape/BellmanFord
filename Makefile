CXX := g++
CXXFLAGS := -std=c++17 -O0 -g

.PHONY: all clean

all: BellmanFord

zip: BellmanFord.cpp Graph.cpp Graph.h Makefile readme.txt readme.pdf
	zip William_Paape_lab1.zip $^

BellmanFord: BellmanFord.o Graph.o
	$(CXX) $(CXXFLAGS) $^ -o $@

BellmanFord.o: BellmanFord.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Graph.o: Graph.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) BellmanFord *.o
