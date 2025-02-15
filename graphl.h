#ifndef MY_EXECUTABLE_GRAPHL_H
#define MY_EXECUTABLE_GRAPHL_H

#include <iostream>
#include <fstream>
#include <climits>
#include <string>

using namespace std;
const int MAX_NODES = 100;

struct EdgeNode;

struct GraphNode {
    EdgeNode* edgeHead; // head of the list of edges, pointer to AL
    string data;     // data information about each node
    bool visited;

};


struct EdgeNode {
    int adjGraphNode; // index to adjacent node
    EdgeNode* nextEdge; // pointer to next edge
};


class GraphL {
public:
    GraphL();
    ~GraphL();
    int buildGraph(ifstream& input);
    void displayGraph() const;
    void depthFirstSearch();


private:
    GraphNode* nodeArray; // array for  GraphNodes
    int size; // # of nodes
    void dfsHelper(int nodeIndex);

};


#endif //MY_EXECUTABLE_GRAPHL_H


/*
 * Notes:
 * GraphNode = node info / desc,  pointer to its adjacency list (AL) of edges, and visited flag
 * EdgeNode = adjacent node index and a pointer to the next edge.
 *
 * Methods: constructor, destructor, int buildGraph, void displayGraph, void depthFirstSearch, void dfsHelper
 *
 *

 */