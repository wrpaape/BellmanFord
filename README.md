| Name              | NetID | Student ID |
|------------------ | ----- | ---------- |
|William Reid Paape | paape | 2877379718 |

# EE450 - BellmanFord


## Overview
- [Purpose](#purpose)
- [Invocation](#invocation)
- [Code Organization](#code-organization)
- [Bellman-Ford Implementation](#bellman-ford-implementation)
- [Input Format](#input-format)
- [Output Format](#output-format)


## Purpose
The purpose of this program is to demonstrate an implementation of the
Distance-Vector Routing Algorithm developed by Bellman and Ford.  Given a
weighted directed graph, this algorithm will determine the shortest (least
expensive) path between any two vertices.


## Invocation
```
./BellmanFord <graph file>
```
where `<graph file>` is the path to an input file formatted according to the
[Input Format](#input-format) section.


## Code Organization
The source code for this demonstration is split across three C++ modules:
- [BellmanFord](#bellmanford)
- [Graph](#graph)
- [PathFinder](#pathfinder)

### BellmanFord
The `BellmanFord` module is the main entry point of the program.  It opens the
supplied graph file, builds a `Graph`, leverages the `PathFinder` module to
find the best path across the `Graph`, and reports the results.  Refer to the
[Output Format](#output-format) section for an explanation of report format
format.  See the `main()` and `report*()` routines in `BellmanFord.cpp` for
implementation details.

### Graph
`Graph` provides an in-memory representation of a graph.  It is constructible
via an input text stream formatted according to the [Input
Format](#input-format) section.  `Graph`'s internal representation is an
adjacency matrix, and it offers access to cost of stepping from node `i` to
node `j` via the bracket operator: `costIJ = graph[i][j];`.  If `i` is
inaccessible from `j`, the cost stored at `graph[i][j]` will be
`Graph::INFINITE_COST`.  See the class declaration in `Graph.h` and
class definition in `Graph.cpp` for implementation details.

### PathFinder
`PathFinder` provides the implementation for Bellman-Ford algorithm.
`PathFinder::findBestPaths()`, the module interface, operates on instances of
`Graph`.  The routine returns a vector describing the "best" (minimum cost) paths
from node `0` to any other node, a "costs" vector describing the minimum cost
from node `0` to any other node, and the number of "iterations" required to
arrive at the solution.  Should any negative loops be detected by
`PathFinder::findBestPaths()`, its returned best-paths vector will describe the
loop(s).  See `PathFinder.h` for the interface prototype, `PathFinder.cpp`
for implementation details, and the [Bellman-Ford
Implementation](#bellman-ford-implementation) section for pseudo code.


## Bellman-Ford Implementation
The pseudo code for the Bellman-Ford implementation is as follows:
```
- provided a matrix of costs named "costs"
    - costs[i][j] is the cost of stepping from node i to node j
- maintain a mapping of nodes to their costs named "minCosts"
- maintain a mapping of nodes to the best path previous node
    - name this "bestPaths"
    - a minimum cost path can be traced from node 0 to another node i
    - the previous node to node i on this path will be stored at bestPaths[i]
- maintain an iteration counter named "iterations"
1. initialize minCosts with Graph::INFINITE_COST
2. initialize paths with an invalid node (i.e. -1)
3. set the cost to travel to node 0
4. set iterations to 0 (minCosts[0] = 0)
5. for up to N-1 iterations:
    a. for every node i:
        I. for every node j accessible from i:
            1. costIJ = minCosts[i] + costs[i][j]
            2. if costIJ < minCosts[j]
                a. minCosts[j] = costIJ
                b. bestPaths[j] = i
    b. increment iterations by 1
    c. break if there was no update to the minCosts mapping
6. return iterations, bestPaths, and minCosts
```
The check `c. break if there was no update to the minCosts mapping` allows the
algorithm to terminate often well before `N-1` iterations have been processed
in the main loop.  Negative loops are detected if an update to `minCosts`
occurs after `N-1` iterations have been processed.  This suggests that further
improvements (`minCosts` updates) can be made after the proven-maximum required
number of iterations, which could only be possible in the case of the presence
of at least one negative loop which will indefinitely drive down `minCosts`
with every negative-cost series of steps taken.  See `PathFinder.cpp` for
implementation details.


## Input Format
The input file shall be a white-space-delimited, human-readable adjacency
matrix describing the cost of traversing all permutations of pairs of nodes.
A graph consisting of `N` nodes numbered `0` through `N-1` shall form an `NxN`
matrix of costs of the form:
```
<cost 0->0> <cost 0->1> ... <cost 0->N-1>
<cost 1->0> <cost 1->1> ... <cost 1->N-1>
...
<cost N-1->0> <cost N-1->1> ... <cost N-1->N-1>
```
where `<cost i->j>` is one of the following forms:
- `inf`: `j` is not directly accessible from `i` (infinite cost). This value is represented internally by the special value `Graph::INFINITE_COST`.
- `<cost>`: a single integer
- `[cost 1,cost 2,...,cost N]`: a bracket-enclosed, comma-delimited list of integers, whose evaluated sum will be stored as the cost


## Output Format
The output of this program will be written to a file `output.txt` in the
current working directory.  The format of this file depends on whether a
negative loop is encountered while operating on the supplied graph.

### Finite Best Path Exists (No Negative Loop(s))
If a minimum-cost/distance "best" path exists in the supplied graph without
encountering any negative loops, `output.txt` will be formatted as follows:
```
<cost 0->0>,<cost 0->1>,...,<cost 0->N-1>
<best path 0->0>
<best path 0->1>
...
<best path 0->N-1>
Iteration:<iterations>
```
where
- `<cost 0->i>` is an integer cost of traveling the path from node `0` to node `i`, or `inf` if node `i` is inaccessible from node `0`
- `<best path 0->i>` is the `->`-delimited best path from node `0` to node `i`
and
- `<iterations>` is the integer number of iterations required for the Bellman-Ford algorithm to terminate
For example:

#### Input
```
0 1 inf 2 inf
inf 0 4 2 inf
inf inf 0 inf 2
inf inf 4 0 2
inf inf inf inf 0
```
or
```
[0,0,0] [0,1,0] inf [1,1,0] inf
inf [0,0,0] [1,1,2] [1,10] inf
inf inf [0,0,0] inf [1,0,1]
inf inf [1,1,2] 0 [0,1,1]
inf inf inf inf [0,0,0]
```
#### Output
```
0,1,5,2,4
0
0->1
0->1->2
0->3
0->3->4
Iteration:3 
```

### Negative Loop(s) Encountered
If at least one negative loop exists, `output.txt` will be formatted as follows:
```
Negative Loop Detected
<start>-><node i>-><node j>->...-><start>
```
where the second line depicts one of the detected negative loops.  If a
negative loop is reachable from node `0`, it will be displayed in preference of
any other negative loops.  For example:

#### Input
```
0 -1 inf
inf 0 -1
-1 inf 0
```
#### Output
```
Negative Loop Detected
0->1->2->0
```

## Experimentation Results
When operating on the provided input files, this implementation of
`BellmanFord` produces results that match their expected output with the
exception of N3.txt, which inconsistently expects a 1-based node numbering
scheme in its output.  Outside of the provided test cases, I tested graphs of
up to 10000 nodes and graphs with unreachable nodes.  This implementation
handles both gracefully.  Unreachable nodes are marked with `inf` cost in their
cost vector entry, and the line `No path from 0 to <node>` is output in place
of their best path.  `BellmanFord` took a few seconds to terminate given a
10000-node graph, and terminated almost immediately for graphs with 1000 or
less nodes.
