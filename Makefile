CXX := g++
CXXFLAGS := -std=c++17 -O0 -g

.PHONY: all zip clean

all: BellmanFord

zip: BellmanFord.cpp Graph.cpp Graph.h PathFinder.cpp PathFinder.h Makefile readme.txt report.pdf
	zip William_Paape_lab1.zip $^

report.pdf: README.md
	pandoc $< -o $@

BellmanFord: BellmanFord.o PathFinder.o Graph.o 
	$(CXX) $(CXXFLAGS) $^ -o $@

BellmanFord.o: BellmanFord.cpp PathFinder.h Graph.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

PathFinder.o: PathFinder.cpp PathFinder.h Graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Graph.o: Graph.cpp Graph.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) BellmanFord *.o report.pdf William_Paape_lab1.zip
