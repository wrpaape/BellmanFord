#include "graph.h"
#include <stdexcept>
#include <sstream>
#include <limits>
#include <algorithm>

const int Graph::INFINITE_COST = std::numeric_limits<int>::max();

Graph::Graph(std::istream &input)
{
    std::string line;
    if (!std::getline(input, line))
        throw std::invalid_argument("empty graph");

    initMatrix(line);

    std::istringstream tokens;
    std::string token;

    auto rowIter = matrix.begin(),
         rowsEnd = matrix.end();
    do {
        tokens.str(line);
        tokens.clear();
        for (auto &cost : *rowIter) {
            if (!(tokens >> token))
                throw std::invalid_argument("not enough graph columns");
            cost = parseCost(token);
        }
    } while (   (++rowIter != rowsEnd)
             && std::getline(input, line));

    if (rowIter != rowsEnd) {
        throw std::invalid_argument("not enough graph rows");
    }
}

std::ostream& operator<<(std::ostream &output, const Graph &graph)
{
    for (const auto &row : graph.matrix) {
        for (const auto cost : row) {
            output << cost << ' ';
        }
        output << std::endl;
    }
}

void
Graph::initMatrix(const std::string &firstLine)
{
    std::size_t countSpaces = std::count(firstLine.begin(),
                                         firstLine.end(),
                                         ' ');
    std::size_t countNodes = countSpaces + 1;

    matrix.resize(countNodes);
    for (auto &row : matrix) {
        row.resize(countNodes);
        std::fill(row.begin(),
                  row.end(),
                  INFINITE_COST);
    }
}

int
Graph::parseCost(const std::string &token)
{
    if (token == "inf")
        return INFINITE_COST;

    if ((token.front() == '[') && (token.back() == ']')) {
        return parseMultiCost(token);
    }

    return std::stoi(token, nullptr);
}

int
Graph::parseMultiCost(const std::string &token)
{
    int totalCost = 0;
    int cost;
    std::istringstream sequence(token);
    while (sequence.ignore() && (sequence >> cost)) {
        totalCost += cost;
    }
    return totalCost;
}
