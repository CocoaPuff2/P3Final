#include "graphm.h"
#include <fstream>
#include <iomanip>
#include <climits>
#include <queue>

using namespace std;

// initialize AM with infinity and table entries
GraphM::GraphM() {
    size = 0;
    for (int i = 0; i < MAXNODES; i++) {
        data[i] = ""; // empty the desc for the nodes
        for (int j = 0; j < MAXNODES; j++) {
            // default value for each
            C[i][j] = INT_MAX;
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = -1;
        }
    }
}

// read data from input
void GraphM::buildGraph(std::istream& input) {
    input >> size; // read # of nodes in graph
    input.ignore(); // debug line: ignore the newline

    // read each node desc using getline
    // getline = read an entire line of text from an input stream including spaces
    for (int i = 0; i < size; i++) {
        getline(input, data[i]);
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = INT_MAX;
        }
    }

    // read edges the populate AM and C
    int startNode, endNode, edgeCost;
    while (input >> startNode >> endNode >> edgeCost) {
        if (startNode == 0 && endNode == 0 && edgeCost == 0) break; // stop if 0 0 0
        int fromIndex = startNode - 1;
        int toIndex = endNode - 1;
        // store in AM
        // convert 1 to 0 based for indexing storage
        C[fromIndex][toIndex] = edgeCost;
    }
}

// Dijkstra
void GraphM::findShortestPath() {
    // loop through possible source nodes in graph
    for (int source = 0; source < size; source ++) {
        // reset table
        for (int i = 0; i < size; i++) {
            T[source][i].dist = INT_MAX;
            T[source][i].visited = false;
            T[source][i].path = -1;
        }

        T[source][source].dist = 0; //  dist from source to source

        // PQ to get smallest dist node
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // put source into PQ with dist = 0 (dist, node)
        pq.push({0, source});

        // process nodes in queue
        while (!pq.empty()) {
            // node with smallest dist from pq, .second` gives us the node
            int checkNode = pq.top().second;
            pq.pop();

            // if node vistsed, skip
            if (T[source][checkNode].visited) continue;

            // mark visited
            (T[source][checkNode].visited) = true;

            // update the distances
            for (int v = 0; v < size; v++) {
                // consider the non visited nodes
                if (!T[source][v].visited && C[checkNode][v] != INT_MAX) {
                    // potential dist
                    int newDist = T[source][checkNode].dist + C[checkNode][v];
                    // if shorter dist
                    if (newDist < T[source][v].dist) {
                        T[source][v].dist = newDist;
                        T[source][v].path = checkNode;
                        pq.push({newDist, v});
                    }
                }

            }
        }

    }
}

void GraphM::displayAll() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (T[i][j].dist == INT_MAX) {
                cout << "No path from " << data[i] << " to " << data[j] << endl;
            } else {
                cout << "From " << data[i] << " to " << data[j] << ": "
                        << "Distance: " << T[i][j].dist << ", Path: ";
                printPath(i, j);  // Print the path from i to j
                cout << endl;
            }
        }
    }

}

void GraphM::display(int from, int to) const {
    // from and to are valid node #s?
    if ( from < 1 || to < 1 || from > size || to > size) {
        cout << "Node input invalid" << endl;
        return;
    }

    // Convert 1-based input to 0-based indexing.
    int src = from - 1, dest = to - 1;

    cout << "shortest path from " << from << " to " << to << ":" << endl;
    if (T[src][dest].dist == INT_MAX) {
        cout << "No path exists" << endl;
    } else {
        cout << "cost: " << endl;
        cout << "path: ";
        printPath(src, dest);
        cout << endl;
    }

}

void GraphM::printPath(int from, int to) const {
    // BC: If the starting node is the same as the destination
    // (reached the destination node, print it)
   if (from == to) {
       cout << data[from] << " ";
       return;
   }
   if (T[from][to].path == -1) {
       cout << "No path.";
       return;
   }
   // Print the path by tracing back through the 'path' array
   // path keeps track of the previous node on the shortest path to each node
   printPath(from, T[from][to].path);
    cout << data[to] << " ";
}