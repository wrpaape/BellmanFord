CXX := g++
CXXFLAGS := -std=c++17 -O0 -g

.PHONY: all clean

all: BellmanFord

BellmanFord: BellmanFord.o graph.o
	$(CXX) $(CXXFLAGS) $^ -o $@

BellmanFord.o: BellmanFord.cpp graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

graph.o: graph.cpp graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) BellmanFord *.o
