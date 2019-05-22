#include "graph.h"
#include <iostream>
#include <fstream>


void
usage(const char *program, std::ostream& output)
{
    output << program << " <graph file>" << std::endl;
}


int
main(int argc, char *argv[])
{
    if (argc != 2) {
        const char *program = (argc > 0) ? argv[0] : "./BellmanFord";
        usage(program, std::cerr);
        return 1;
    }

    std::ifstream graphFile(argv[1]);

    Graph graph(graphFile);

    std::cout << graph;

    // graph.findPath(start, finish, std::cout);
    
    return 0;
}
