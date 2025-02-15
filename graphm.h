/*
 * Dijkstra's shortest path algorithm.
 * read a data file consisting of many lines and find the lowest cost paths (findShortestPath function)
 * and display the cost and path from every node to every other node (displayAll function).
 * Another display routine (display function) will output one path in detail.
 */
#ifndef MY_EXECUTABLE_GRAPHM_H
#define MY_EXECUTABLE_GRAPHM_H

#include <iostream>
#include <fstream>
#include <climits>
#include <string>

const int MAXNODES = 100;

// 1. Class Attributes: array of string, the adjacency matrix, number of nodes, and TableType array.

class GraphM {
public:
    GraphM();
    int buildGraph(std::istream& input);
    int insertEdge(int, int, int);
    int removeEdge(int, int);
    void findShortestPath();
    void displayAll() const;
    void display(int from, int to) const;

private:
    struct TableType {
        bool visited;          // whether node has been visited
        int dist;              // shortest distance from source node to "this" node
        int path;              // store previous node in path of min dist to help construct shortest path
    };

    std::string data[MAXNODES];
    int C[MAXNODES][MAXNODES];
    int size;
    TableType T[MAXNODES][MAXNODES];

    // utility
    void printPath(int from, int to) const;
    void printPathNames(int, int) const;
    int findV(int);

};

// findShortestPath: read a data file consisting of many lines and find the lowest cost paths
/* ex: data31.txt,  first line is the number of nodes (n) followed by a text description of each
 *  of the 1 through n nodes (n max = 100)
 * one desc per line (max 50 char)
 *
 * Each line consists of 3 integers representing an edge
 * ex: . If there is an edge from node 1 to node 2 with a weight of 10, the data is: 1 2 10
 *  If the first integer is zero, it means that it is the end of the line for that graph
 *
 */

// displayAll: display the cost and path from every node to every other node

// display function: output one path in detail.

#endif //MY_EXECUTABLE_GRAPHM_H
