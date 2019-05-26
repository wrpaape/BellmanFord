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
    /**
     * @brief constructor for a Graph instance
     * @param[in,out] input stream containing the adjacency matrix
     *     representation of the graph
     */
    Graph(std::istream &input);

    /**
     * @brief append the text representation of @p graph to @output
     * @param[out] output stream where @p graph will be writen
     * @param[in]  graph the graph to be inspected
     * @return reference to @p output
     */
    friend std::ostream& operator<<(std::ostream &output, const Graph &graph);

    /**
     * @brief Finds the lowest-cost path from node 0 to node N-1 using the
     *     Bellman–Ford algorithm.
     * @return { <iteration count> >= 1, <path vector>, <cost vector> } if the
     *     algorithm terminates without encountering a negative loop.  If a
     *     negative loop is encountered, return { 0, <path vector>, nullopt }.
     */
    std::tuple<
        unsigned long,
        std::vector<long>,
        std::optional<std::vector<long>>
    >
    findBestPath();

    /**
     * a cost value reserved to represent infinity
     * If it costs INFINITE_COST to step from node i to node j, then node j is
     * not accessible from node i.
     */
    static const long INFINITE_COST;

private:
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
