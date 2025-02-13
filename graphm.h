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
    int buildGraph(std::istream& input); // read graph data from input
    // todo just added
    int insertEdge(int from, int to, int cost);
    int removeEdge (int from, int to);

    void findShortestPath(); // djikstra alg
    void displayAll() const; // display shortest path all nodes
    void display(int from, int to) const; //  display single shortest path
    // note: changed from void to int

    void dfsHelper(int) const;

private:
    // TableType is a struct to keep the current shortest distance (and associated path info)
    // known at any point in the algorithm.
    struct TableType {
        bool visited;          // whether node has been visited
        int dist;              // shortest distance from source node to "this" node
        int path;              // store previous node in path of min dist to help construct shortest path
    };

    std::string data[MAXNODES];              // data for graph nodes
    int C[MAXNODES][MAXNODES];            // Cost array, the adjacency matrix
    int size;                             // number of nodes in the graph
    TableType T[MAXNODES][MAXNODES];      // stores visited, distance, path

    // T = 2-dimensional array of structs so we can work on from all nodes to all other nodes.
    void printPath(int from, int to) const;

};

// 2. PSEUDOCODE
/*
 * for (int source = 1; source <= nodeSize; source++) {

      T[source][source].dist = 0;



      // finds the shortest distance from source to all other nodes

      for (int i = 1; i<= nodeSize; i++) {

         find v //not visited, shortest distance at this point

         mark v visited

         for each w adjacent to v

           if (w is not visited)

            T[source][w].dist=min(T[source][w].dist, T[source][v].dist+C[V][W])

      }

   }
 *
 */

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
