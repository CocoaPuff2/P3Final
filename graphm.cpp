#include "graphm.h"
#include <fstream>
#include <iomanip>
#include <limits>

using namespace std;

// initialize AM with infinity and table entries
GraphM::GraphM() {
    size = 0;
    for (int i = 0; i < MAXNODES; i++) {
        for (int j = 0; j < MAXNODES; j++) {
            // If the node refers to itself, set cost to 0 (no travel cost).
            // else, set cost to INT_MAX
            if (i == j) {
                C[i][j] = 0;
            } else {
                C[i][j] = INT_MAX;
            }

            // mark that node as visited
            T[i][j].visited = false;
            // sets intial short dist
            T[i][j].dist = INT_MAX;
            // indicate that no known prev node
            T[i][j].path = -1;

        }
    }
}

// read data from input
void GraphM::buildGraph(std::istream& input) {
    input >> size; // read # of nodes in graph
    input.ignore(); // ignore newline

    // read each node desc using getline
    // getline = read an entire line of text from an input stream including spaces
    for (int i = 0; i < size; i++) {
        getline(input, data[i]);
    }

    int startNode, endNode, edgeCost;

    while (input >> startNode >> endNode >> edgeCost) {
        if (startNode == 0) break; // stop if 0 0 0
        int fromIndex = startNode - 1;
        int toIndex = endNode - 1;

        // store in AM
        // convert 1 to 0 based for indexing storage
        C[fromIndex][toIndex] = edgeCost;
    }
}

void GraphM::findShortestPath() {
    // loop through possible source nodes in graph
    for (int startNode = 0; startNode < size; startNode ++) {
        T[startNode][startNode].dist = 0; // dist to itself is 0

        // process each node to find shortest path
        for (int count = 0; count < size; count++) {
            int minDist = INT_MAX;
            int closestDistance = -1;
        }
    }
}

void GraphM::displayAll() const {

}

void GraphM::display(int from, int to) const {

}

void GraphM::printPath(int from, int to) const {

}