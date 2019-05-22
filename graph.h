#ifndef GRAPH_H
#define GRAPH_H

#include <istream>
#include <ostream>
#include <vector>

class Graph
{
public:
    Graph(std::istream &input);

    friend std::ostream& operator<<(std::ostream &output, const Graph &graph);

private:
    static const int INFINITE_COST;

    std::vector<std::vector<int>> matrix;

    int
    parseCost(const std::string &token);

    int
    parseMultiCost(const std::string &token);

    void
    initMatrix(const std::string &firstLine);
};

#endif // GRAPH_H
