#include "graph.h"
#include <stdexcept>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iostream>

const long Graph::INFINITE_COST = std::numeric_limits<long>::max();

Graph::Graph(std::istream &input)
{
    std::string line;
    if (!std::getline(input, line))
        throw std::invalid_argument("empty graph");

    initMatrix(line);

    std::istringstream tokens;
    std::string token;

    auto rowIter = stepCostMatrix.begin(),
         rowsEnd = stepCostMatrix.end();
    do {
        tokens.str(line);
        tokens.clear();
        for (auto &stepCostMatrix : *rowIter) {
            if (!(tokens >> token))
                throw std::invalid_argument("not enough graph columns");
            stepCostMatrix = parseCost(token);
        }
    } while (   (++rowIter != rowsEnd)
             && std::getline(input, line));

    if (rowIter != rowsEnd) {
        throw std::invalid_argument("not enough graph rows");
    }
}

std::tuple<
    long,
    std::vector<long>,
    std::optional<std::vector<long>>
>
Graph::findBestPath()
{
    std::vector<long> minCosts(stepCostMatrix.size(), INFINITE_COST);
    std::vector<long> bestPath(stepCostMatrix.size(), -1);
    bool updated = false;
    minCosts.front() = 0;
    long iterations = 1;
    do {
        updated = false;
        for (long node = 0; node < stepCostMatrix.size(); ++node) {
            updated |= takeStep(node,
                                stepCostMatrix[node],
                                minCosts,
                                bestPath);
        }
        ++iterations;
        // for (auto cost : minCosts) {
        //     std::cout << cost << ' ';
        // }
        // std::cout << std::endl;
    } while (updated && (iterations < stepCostMatrix.size()));

    if (!updated) {
        return {
            iterations,
            std::move(bestPath),
            std::make_optional(std::move(minCosts))
        };
    }

    return {
        0,
        std::move(bestPath),
        std::nullopt
    };
}

std::ostream& operator<<(std::ostream &output, const Graph &graph)
{
    for (const auto &row : graph.stepCostMatrix) {
        for (const auto stepCostMatrix : row) {
            output << stepCostMatrix << ' ';
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

    stepCostMatrix.resize(countNodes);
    for (auto &row : stepCostMatrix) {
        row.resize(countNodes);
        std::fill(row.begin(),
                  row.end(),
                  INFINITE_COST);
    }
}

long
Graph::parseCost(const std::string &token)
{
    if (token == "inf")
        return INFINITE_COST;

    if ((token.front() == '[') && (token.back() == ']')) {
        return parseMultiCost(token);
    }

    return std::stol(token, nullptr);
}

long
Graph::parseMultiCost(const std::string &token)
{
    long totalCost = 0;
    long stepCostMatrix;
    std::istringstream sequence(token);
    while (sequence.ignore() && (sequence >> stepCostMatrix)) {
        totalCost += stepCostMatrix;
    }
    return totalCost;
}

bool
Graph::addWillOverflow(long x, long y)
{
    return ((y > 0) && (x > (std::numeric_limits<long>::max() - y)))
        || ((y < 0) && (x < (std::numeric_limits<long>::min() - y)));
}

bool
Graph::takeStep(long                     prevNode,
                const std::vector<long> &stepCosts,
                std::vector<long>       &minCosts,
                std::vector<long>       &bestPath)
{
    bool updated = false;
    long minCostToPrev = minCosts[prevNode];
    for (long nextNode = 0; nextNode < stepCosts.size(); ++nextNode) {
        long stepCostPrevNext = stepCosts[nextNode];
        if (addWillOverflow(minCostToPrev, stepCostPrevNext)) {
            continue;
        }
        long totalCostNext = minCostToPrev + stepCostPrevNext;
        long &minCostNext  = minCosts[nextNode];
        if (totalCostNext < minCostNext) {
            minCostNext        = totalCostNext;
            bestPath[nextNode] = prevNode;
            updated            = true;
        }
    }
    return updated;
}
