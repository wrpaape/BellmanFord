#include "graph.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <stdexcept>
#include <algorithm>

namespace {

void
usage(const char *program, std::ostream& output)
{
    output << program << " <graph file>" << std::endl;
}

bool
isLoop(const std::vector<long> &paths,
       long                     dest)
{
    long node = dest;
    while (true) {
        node = paths[node];
        if (node == dest) {
            return true; // looped back to self
        }
        if (node == 0) {
            return false; // back to start
        }
    }
}

std::vector<long>
getPath(const std::vector<long> &paths,
        long                     start,
        long                     dest)
{
    std::vector<long> path;
    int prevNode = dest;
    while (true) {
        path.emplace_back(prevNode);
        if (prevNode == start) {
            break;
        }
        prevNode = paths[prevNode];

        if (prevNode < 0) {
            path.clear();
            break;
        }
    }
    std::reverse(path.begin(), path.end());
    return path;
}

void
reportPath(const std::vector<long> &path,
           std::ostream             &output)
{
    auto pathIter = path.cbegin();
    auto pathEnd  = path.cend();
    while (true) {
        output << *pathIter;
        if (++pathIter == pathEnd) {
            break;
        }
        output << "->";
    }
    output << std::endl;
}

long
findLoop(const std::vector<long> &paths)
{
    for (long dest = paths.size() - 1; dest > 0; --dest) {
        if (isLoop(paths, dest)) {
            return dest;
        }
    }
    std::runtime_error("failed to find expected loop");
}

void
reportNegativeLoop(const std::vector<long> &paths,
                   std::ostream            &output)
{
    output << "Negative Loop Detected" << std::endl;
    long destLoop = findLoop(paths);
    std::vector<long> loop = getPath(paths, destLoop, destLoop);
    if (loop.empty()) {
        throw std::runtime_error("no loop found");
    }
    reportPath(loop, output);
}


void
reportBestPaths(const std::vector<long> &minCosts,
                const std::vector<long> &paths,
                long                     iterations,
                std::ostream            &output)
{
    auto costsIter = minCosts.cbegin();
    auto costsEnd  = minCosts.cend();
    while (true) {
        output << *costsIter;
        if (++costsIter == costsEnd) {
            break;
        }
        output << ',';
    }
    output << std::endl;

    for (long dest = 0; dest < paths.size(); ++dest) {
        std::vector<long> path = getPath(paths, 0, dest);
        if (!path.empty()) {
            reportPath(path, output);
        } else {
            output << "No path from 0 to " << dest << std::endl;
        }
    }

    output << "Iteration:" << iterations << std::endl;
}

} // namespace


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

    // std::cout << graph;

    auto [iterations, paths, minCosts] = graph.findBestPath();

    if (iterations > 0) {
        reportBestPaths(*minCosts, paths, iterations, std::cout);
    } else {
        reportNegativeLoop(paths, std::cout);
    }
    
    return 0;
}
