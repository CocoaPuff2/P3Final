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
        return -1; // if node number invalid
    }

    // alloc mem for nodeArray (array that contains GraphNodes)
    nodeArray = new GraphNode[size];
    for (int i = 0; i < size; i++) {
        nodeArray[i].edgeHead = nullptr; // head of edge list == nullptr
        nodeArray[i].visited = false;
        getline(input, nodeArray[i].data); // read node data

        // read edges for current node
        int numberEdges;
        input >> numberEdges;
        for (int j = 0; j < numberEdges; j++) {
            int adjNode;
            input >> adjNode; // read index of adjacent node

            // create new edge node,  put at beginning of edge list
            EdgeNode* newEdge = new EdgeNode; // store adjacent node
            newEdge->adjGraphNode = adjNode - 1; // link edge to prev head
            newEdge->nextEdge = nodeArray[i].edgeHead; // update head
        }
        input.ignore();
    }
    return 1; // success
}

void GraphL::displayGraph() const {
    // goes through each node and displays edges
    for (int i = 0; i < size; i++) {
        cout << "Node " << i + 1 << ": " << nodeArray[i].data << endl;
        EdgeNode* edge = nodeArray[i].edgeHead;  // Start from the head of the edge list
        // display edges
        while (edge != nullptr) {
            cout << " Edge to Node " << edge->adjGraphNode + 1 << endl;
            edge = edge->nextEdge;
        }

    }
}

void GraphL::dfsHelper(int nodeIndex) const {
    nodeArray[nodeIndex].visited = true;
    cout << nodeIndex + 1 << " ";

    EdgeNode* edge = nodeArray[nodeIndex].edgeHead;
    while (edge != nullptr) {
        if (!nodeArray[edge->adjGraphNode].visited) {
            dfsHelper(edge->adjGraphNode);
        }
        edge = edge->nextEdge;
    }
}

void GraphL::depthFirstSearch() const {
    for (int i = 0; i < size; i++) {
        nodeArray[i].visited = false;
    }

    for (int i = 0; i < size; i++) {
        if (!nodeArray[i].visited) {
            dfsHelper(i);
        }
    }
}
