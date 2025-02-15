#include "graphl.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

GraphL::GraphL() {
    size = 0;
    nodeArray = new GraphNode[MAX_NODES + 1];
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
void GraphL::resetGraph() {
    // Reset the node array and edge list
    for (int i = 1; i <= size; ++i) {
        nodeArray[i].data = "";  // Clear node data
        nodeArray[i].visited = false;  // Reset visited flag
        EdgeNode* current = nodeArray[i].edgeHead;

        // Clear all edges
        while (current != nullptr) {
            EdgeNode* temp = current;
            current = current->nextEdge;
            delete temp;  // Free memory
        }

        // Set edgeHead to nullptr to reset the edge list
        nodeArray[i].edgeHead = nullptr;
    }
}

//  Reads graph data from input and builds the graph structure
// 1. read # of nodes (n) from input file
// 2. allocate mem for graph nodes (array of GraphNode)
// 3. read node desc and store in data
// 4. read edges and build AL for each node (add EdgeNode objects)
// 5 set up AL for each node, insert edges in reverse order

int GraphL::buildGraph(std::ifstream& input) {
    int from, to;
    resetGraph();


    if (input.eof()) {
         cout << "Error: File reached EOF before reading size!" << endl;
        return -1;
    }

    if (!input.good()) {
         cout << "Error: Stream is in a bad state!" << endl;
        input.clear();
        input.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (!(input >> size)) {
         cout << "Error: Could not read graph size!" << endl;
        return -1;
    }
    /*
    streampos pos_after_size = input.tellg();
    cout << "Position after reading size: " << pos_after_size << endl;
     */

    //  cout << "DEBUG: Read graph size: " << size << endl;

    if (size <= 0 || size > MAX_NODES) {
         cout << "Invalid graph size: " << size << endl;
        return -1;
    }

   input.ignore(numeric_limits<streamsize>::max(), '\n');
    /*
    streampos pos_after_ignore = input.tellg();
    cout << "Position after ignore: " << pos_after_ignore << endl;
     */

    //cout << "Reading " << size << " nodes..." << endl;

    for (int i = 1; i <= size; i++) {
        if (!getline(input >> ws, nodeArray[i].data)) return -1;
        if (!nodeArray[i].data.empty() && nodeArray[i].data.back() == '\r') {
            nodeArray[i].data.pop_back();
        }
       //  cout << "Node " << i << " data: " << nodeArray[i].data << endl;
    }
    // cout << "Reading edges..." << endl;
    while (input >> from >> to) {
        // cout << "Edge read: " << from << " -> " << to << endl;
        if (from == 0) break;
        // Create a new edge node and link it to the appropriate node in the graph
        // EdgeNode* newEdge = new EdgeNode;
        EdgeNode* newEdge = new EdgeNode;
        newEdge->adjGraphNode = to;
        newEdge->nextEdge = nodeArray[from].edgeHead;
         nodeArray[from].edgeHead = newEdge;

    }

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
    for (int i = 1; i <= size; i++) {
        cout << "Node " << i << "        " << nodeArray[i].data << endl;
        // cout << "Node " << i << "       " << nodeArray[i].data << endl;

        EdgeNode* edge = nodeArray[i].edgeHead;  // start from head of edge list
        while (edge != nullptr) {
            cout << "  edge " << i << " " << edge->adjGraphNode << endl;
            edge = edge->nextEdge;
        }
        cout << endl;
    }
}

void GraphL::depthFirstSearch(){
    cout << "Depth-first ordering: ";

    // mark all nodes as unvisited
    for (int i = 1; i <= size; i++) {
        nodeArray[i].visited = false;
    }

    // start DFS from each (unvisitied) node
    for (int i = 1; i <= size; i++) {
        if (!nodeArray[i].visited) {
            dfsHelper(i);
        }
    }
    cout << endl;
}

void GraphL::dfsHelper(int nodeIndex) {
    // mark the node as visited
    nodeArray[nodeIndex].visited = true;

    cout << nodeIndex << " ";

    // traverse AL of node
    EdgeNode* edge = nodeArray[nodeIndex].edgeHead;
    while (edge != nullptr) {
        // if adjacent node unvisited, DFS
        if (!nodeArray[edge->adjGraphNode].visited) {
            dfsHelper(edge->adjGraphNode);
        }
        edge = edge->nextEdge;
    }

}