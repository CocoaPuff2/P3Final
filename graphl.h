#ifndef MY_EXECUTABLE_GRAPHL_H
#define MY_EXECUTABLE_GRAPHL_H

#include <iostream>
#include <fstream>
#include <climits>
#include <string>

using namespace std;


struct EdgeNode;      // forward reference for the compiler

struct GraphNode {    // structs used for simplicity, use classes if desired
    EdgeNode* edgeHead; // head of the list of edges
    string data;     // data information about each node
    bool visited;

};



struct EdgeNode {
    int adjGraphNode;  // subscript of the adjacent graph node
    EdgeNode* nextEdge;
};


class GraphL {
public:
    GraphL();
    ~GraphL();
    int buildGraph(ifstream& input);
    void displayGraph() const;
    void depthFirstSearch() const;


private:
    // array of GraphNodes
    GraphNode* nodeArray; // array for GraphNodes
    int size; // # of nodes
    void dfsHelper(int nodeIndex) const;

};


#endif //MY_EXECUTABLE_GRAPHL_H
