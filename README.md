| Name              | NetID | Student ID |
|------------------ | ----- | ---------- |
|William Reid Paape | paape | 2877379718 |

# EE450 - BellmanFord


## Overview
- [Purpose](#purpose)
- [Code Organization](#code-organization)
- [Input Format](#input-format)
- [Output Format](#output-format)


## Purpose
The purpose of this program is to demonstrate an implementation of the
Distance-Vector Routing Algorithm developed by Bellman and Ford.  Given a
weighted directed graph, this algorithm will determine the shortest (least
expensive) path between any two vertices.


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
format.

### Graph
`Graph` provides an in-memory representation of a graph.  It is constructible
via an input text stream formatted according to the [Input
Format](#input-format) section.  `Graph`'s internal representation is an
adjacency matrix, and it offers access to cost of stepping from node `i` to
node `j` via the bracket operator: `costIJ = graph[i][j];`.  If `i` is
inaccessible from `j`, the cost stored at `graph[i][j]` will be
`Graph::INFINITE_COST`.

### PathFinder
`PathFinder` provides the implementation for Bellman-Ford algorithm.  It
operates on instances of `Graph`.


## Implementation


## Input Format


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

