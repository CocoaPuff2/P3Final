#include "graphl.h"
#include <iostream>
#include <fstream>
#include <climits>
#include <string>

using namespace std;

GraphL::GraphL() {
    size = 0;
    nodeArray = nullptr;
}

GraphL::~GraphL() {
    // free the memory used by nodes and edges if (nodeArray != nullptr) {
    if (nodeArray != nullptr) {
        //  delete its edge list (if any) for each node, starting with head
        for (int i = 0; i < size; i++) {
            EdgeNode* edge = nodeArray[i].edgeHead;
            // traverse thru LL of nodes
            while (edge != nullptr) {
                EdgeNode* temp = edge; // store current node edge
                edge = edge->nextEdge; // move to next node
                delete temp; // free mem
            }
        }
        delete[] nodeArray; // dealloc entire array
    }

}

//  Reads graph data from input and builds the graph structure
// 1. 1st line of input gives # of  nodes in the graph
// 2. description of each node in next lines & node's edges
// 3. allocate memory for the nodeArray based on # nodes & populate nodeArray with data
// 4.  Each node will have its edge list constructed dynamically.
int GraphL::buildGraph(ifstream& input) {
    input >> size;
    if (size <= 0) {
        return -1;
    }

    // alloc mem for nodeArray (array that contains GraphNodes)
    nodeArray = new GraphNode[size];
    for (int i = 0; i < size; i++) {
        nodeArray[i].edgeHead = nullptr;
        nodeArray[i].visited = false;
        getline(input, nodeArray[i].data);
    }
}

void GraphL::displayGraph() const {

}
void GraphL::depthFirstSearch() const {

}
