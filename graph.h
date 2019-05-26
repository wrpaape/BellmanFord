#ifndef GRAPH_H
#define GRAPH_H

#include <istream>
#include <ostream>
#include <vector>
#include <tuple>
#include <optional>

class Graph
{
public:
    Graph(std::istream &input);

    friend std::ostream& operator<<(std::ostream &output, const Graph &graph);

    std::tuple<
        long,
        std::vector<long>,
        std::optional<std::vector<long>>
    >
    findBestPath();

private:
    static const long INFINITE_COST;

    std::vector<std::vector<long>> stepCostMatrix;

    static long
    parseCost(const std::string &token);

    static long
    parseMultiCost(const std::string &token);

    void
    initMatrix(const std::string &firstLine);

    static bool
    addWillOverflow(long x, long y);

    static bool
    takeStep(long               prevNode,
             const std::vector<long>    &stepCosts,
             std::vector<long>       &minCosts,
             std::vector<long>       &bestPath);
};

#endif // GRAPH_H
