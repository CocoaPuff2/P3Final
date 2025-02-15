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

//  Reads graph data from input and builds the graph structure
// 1. read # of nodes (n) from input file
// 2. allocate mem for graph nodes (array of GraphNode)
// 3. read node desc and store in data
// 4. read edges and build AL for each node (add EdgeNode objects)
// 5 set up AL for each node, insert edges in reverse order

int GraphL::buildGraph(std::ifstream& input) {
    int from, to;


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
        EdgeNode* newEdge = new EdgeNode;
        newEdge->adjGraphNode = to;
        // todo
        newEdge->nextEdge = nodeArray[from].edgeHead; // Point new edge to the current head of the list

        // Link the new edge as the head of the adjacency list for the 'from' node
        nodeArray[from].edgeHead = newEdge;

        // If the graph is undirected, repeat the process for the reverse edge
        // Create the reverse edge (from to node) if the graph is undirected
        EdgeNode* reverseEdge = new EdgeNode;
        reverseEdge->adjGraphNode = from;
        reverseEdge->nextEdge = nodeArray[to].edgeHead; // Point reverse edge to the current head of the list
        nodeArray[to].edgeHead = reverseEdge;

    }

    return 1;

    /*

    while (input >> from >> to) {
        cout << "Edge read: " << from << " -> " << to << endl;  // Debug output
        // Stop if edge input is "0 0"
        if (from == 0) break;
        // Create a new edge node and link it to the appropriate node in the graph
        EdgeNode* node = new EdgeNode;
        node->adjGraphNode = to;
        node->nextEdge = nodeArray[from].edgeHead;
        nodeArray[from].edgeHead = node;
    }
    return 1;
    /*

    while (input >> from >> to) {
        cout << "Edge read: " << from << " -> " << to << endl;  // Debug output

        if (from == 0) break;  // Stop at 0

        EdgeNode* node = new EdgeNode;
        node->adjGraphNode = to;
        node->nextEdge = nodeArray[from].edgeHead;
        nodeArray[from].edgeHead = node;
    }

     */
    return 1; // todo remove

    /*
    for (int i = 1; i <= size; i++) {
        string str;
        cout << "Create str" << endl;
        if (!getline(input, str)) {
            cout << "Error reading node " << i << endl;
            return -1;
        }
        cout << "Read str" << endl;

        cout << "Assign data " <<  endl;
        cout << "node array at " << i << " " << nodeArray[i].data << endl;
        nodeArray[i].data = str;
        cout << "data at  " << i << " " << nodeArray[i].data <<  endl;


        nodeArray[i].edgeHead = nullptr;
        nodeArray[i].visited = false;
        cout << "Node " << i << ": " << str << endl;  // Debug output
    }

    for (int i = 1; i <= size; i++) {
        string str;
        if (!getline(input, str)) {
             cout << "Error reading node " << i << endl;
            return -1;
        }

        nodeArray[i].data = str;
        nodeArray[i].edgeHead = nullptr;
        nodeArray[i].visited = false;
        cout << "Node " << i << ": " << str << endl;  // Debug output
    }

    cout << "Reading edges..." << endl;
    while (input >> from >> to) {
         cout << "Edge read: " << from << " -> " << to << endl;  // Debug output

        if (from == 0) break;  // Stop at 0

        EdgeNode* node = new EdgeNode;
        node->adjGraphNode = to;
        node->nextEdge = nodeArray[from].edgeHead;
        nodeArray[from].edgeHead = node;
    }

    cout << "Graph built successfully!" << endl;
    return 1;
     */

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