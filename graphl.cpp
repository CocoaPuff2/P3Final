#include "graphl.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

GraphL::GraphL() {
    size = 0;
    nodeArray = nullptr;
}

GraphL::~GraphL() {
    // free  memory used by nodes and edges
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
// 1. read # of nodes (n) from input file
// 2. allocate mem for graph nodes (array of GraphNode)
// 3. read node desc and store in data
// 4. read edges and build AL for each node (add EdgeNode objects)
// 5 set up AL for each node, insert edges in reverse order

int GraphL::buildGraph(ifstream& input) {
    input >> size;
    if (size <= 0) {
        return -1; // if node number invalid
    }

    input.ignore(); // todo

    // 2. alloc mem for nodeArray (array of GraphNodes)
    // creates array of 6 indices, start at index 1
    nodeArray = new GraphNode[size + 1]; // NOTE: use 1 based index


    // 3. read desc for each node
    // for (int i = 0; i < size; i++)
    for (int i = 1; i <= size; i++) {
        getline(input, nodeArray[i].data);  // read node's data
        cout << "Node " << i << " Data: " << nodeArray[i].data << endl;
        nodeArray[i].edgeHead = nullptr;    // head of edge list == nullptr
        nodeArray[i].visited = false;
    }

    // TOOD: work on why the data is not being read from input and being stored in nodeArray[i].data!
    cout << "\nNodeArray after initialization:" << endl;
    for (int i = 1; i <= size; i++) {
        cout << "Node " << i << ": " << endl;
        cout << "  Data: " << nodeArray[i].data << endl;
        cout << "  Edge Head: " << (nodeArray[i].edgeHead ? "Not nullptr" : "nullptr") << endl;
        cout << "  Visited: " << (nodeArray[i].visited ? "true" : "false") << endl;
    }

    cout << "4. in buildGraph" << endl;
    // 4. read edges and build AL for each node (add EdgeNode objects)
    int fromNode, toNode;
    while (true) {
        // todo: fix this line, should be input 1 and 5 initially
        input >> fromNode >> toNode;

        // BC: 0 0
        if (fromNode == 0 && toNode == 0) {
            break;
        }

        // EdgeNode for edge from fromNode to toNode
        EdgeNode* newEdge = new EdgeNode;
        newEdge->adjGraphNode = toNode; //  adjacent to toNode
        newEdge->nextEdge = nodeArray[fromNode].edgeHead;  // point to current head of AL for fromNode

        // 5. insert in reverse order (at beginning of AL)
        nodeArray[fromNode].edgeHead = newEdge; //  make new edge the first edge in AL for fromNode
    }
    cout << "FINISHED BG" << endl;
    return 1;
}


/*
 * Output format:

 Graph:

Node 1       Aurora and 85th

  edge 1 2

  edge 1 3

  edge 1 5
  ....

Depth-first ordering: 1 2 4 3 5

 */
void GraphL::displayGraph() const {
    cout << "Graph:\n";

    // goes through each node and displays edges
    for (int i = 0; i < size; i++) {
        cout << "Node " << i + 1 << "       " << nodeArray[i].data << endl;

        EdgeNode* edge = nodeArray[i].edgeHead;  // start from head of edge list
        while (edge != nullptr) {
            cout << "  edge " << i + 1 << " " << edge->adjGraphNode << endl;
            edge = edge->nextEdge;
        }

    }
}

void GraphL::depthFirstSearch(){
    cout << "\nDepth-first ordering: ";

    // mark all nodes as unvisited
    for (int i = 0; i < size; i++) {
        nodeArray[i].visited = false;
    }

    // start DFS from each (unvisitied) node
    for (int i = 0; i < size; i++) {
        if (!nodeArray[i].visited) {
            dfsHelper(i);
        }
    }
    cout << endl;
}

void GraphL::dfsHelper(int nodeIndex) {
    // mark the node as visited
    nodeArray[nodeIndex].visited = true;

    cout << nodeIndex + 1 << " ";

    // traverse AL of node
    EdgeNode* edge = nodeArray[nodeIndex].edgeHead;
    while (edge != nullptr) {
        // if adjacent node unvisited, DFS
        if (!nodeArray[edge->adjGraphNode - 1].visited) {
            dfsHelper(edge->adjGraphNode - 1);
        }
        edge = edge->nextEdge;
    }

}