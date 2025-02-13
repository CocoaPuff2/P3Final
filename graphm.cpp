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
int GraphM::buildGraph(std::istream& input) {
    input >> size; // read # of nodes in graph
    input.ignore(); // debug line: ignore the newline

    // read each node desc using getline
    // getline = read an entire line of text from an input stream including spaces
    for (int i = 1; i <= size; i++) {
        getline(input, data[i]);
    }

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            C[i][j] = INT_MAX;
        }
    }

    // read edges the populate AM and C
    int startNode, endNode, edgeCost;
    while (input >> startNode >> endNode >> edgeCost) {
        if (startNode == 0) break; // stop if 0 0 0
        int fromIndex = startNode;
        int toIndex = endNode;
        // store in AM
        C[fromIndex][toIndex] = edgeCost;
    }
    return size;
}

// Dijkstra
/*
 * Pseudocode
T[source][w].dist = INT_MAX
T[source][w].visited = false

T[1][1].dist = 0
T[1][2].dist = INT_MAX
T[1][3].dist = INT_MAX
T[1][4].dist = INT_MAX
T[1][5].dist = INT_MAX

 AM
C[1][2] = 50
C[1][3] = 20
C[1][5] = 30
C[2][4] = 10
C[3][2] = 20
C[3][4] = 40
C[5][2] = 20
C[5][4] = 25

 *** First Iteration: findShortestPath ***
 v: The node with the smallest known distance that has not been visited yet.
 T[1][1].visited = true
    For each w (adjacent nodes) update neighbor distances:
    T[source][w].dist=min(T[source][w].dist, T[source][v].dist+C[V][W])
        T[1][2].dist = min(INT_MAX, 0 + 50) = 50 --> largest (c)
        T[1][3].dist = min(INT_MAX, 0 + 20) = 20 --> smallest (a)
        T[1][5].dist = min(INT_MAX, 0 + 30) = 30 --> 2nd smallest (b)

 (c) T[1][2].visited = true
 For each w (adjacent nodes) update neighbor distances:
    T[source][w].dist=min(T[source][w].dist, T[source][v].dist+C[V][W])
        T[1][4].dist = min(INT_MAX, 50(dist 1 to 2) + 10(dist 2 to 4)) = 60

 (a) T[1][3].visited = true
    For each w (adjacent nodes) update neighbor distances:
    T[source][w].dist=min(T[source][w].dist, T[source][v].dist+C[V][W])
        T[1][2].dist = min(50, 20(dist from 1 to 3) + 20(dist from 3 to 2)) = 40
        T[1][4].dist = min(60, 20(dist 1 to 3) + 40(dist 3 to 4)) = 60

(b) T[1][5].visited = true
 For each w (adjacent nodes) update neighbor distances:
    T[source][w].dist=min(T[source][w].dist, T[source][v].dist+C[V][W])
        T[1][2].dist = min(50, 30(dist from 1 to 5) + 20(dist from 5 to 2)) = 40
        T[1][4].dist = min(60, 30(dist 1 to 5) + 25(dist 5 to 4)) = 55


 All nodes are now visited
T[1][1].dist = 0
T[1][2].dist = 40 (1, 3, 2)
T[1][3].dist = 20 (1, 3)
T[1][4].dist = 60 (1, 2, 4)
T[1][5].dist = 30 (1, 5)

 Path for 1-4
 1 → 3 → 2 → 4


 */
void GraphM::findShortestPath() {
    // loop through possible source nodes in graph
    for (int source = 1; source <= size; source ++) {
        // reset table
        for (int i = 1; i <= size; i++) {
            T[source][i].dist = INT_MAX;
            T[source][i].visited = false;
            T[source][i].path = -1;
        }

        T[source][source].dist = 0; //  dist from source to source



        /*
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
         */

    }
}

void GraphM::displayAll() const {
    // Iterate through all the nodes
    for (int from = 1; from <= size; ++from) {
        // Print the node's name at the beginning of each section
        cout << left << setw(25) << data[from - 1] << endl;

        // Print the table header
        cout << left << setw(35) << "Description" << setw(15) << "From node"
             << setw(15) << "To node" << setw(15) << "Distance" << "Path" << endl;

        // Now print the paths for the current node
        for (int to = 1; to <= size; ++to) {
            // Print the node name, and details about the "from" and "to" nodes
            cout << left << setw(35) << data[from - 1] << setw(15) << from
                 << setw(15) << to;

            if (T[from - 1][to - 1].dist == INT_MAX) {
                cout << "---" << setw(15) << endl;
            } else {
                cout << setw(15) << T[from - 1][to - 1].dist;
                printPath(from - 1, to - 1);  // Print the path for this pair
                cout << endl;
            }
        }
    }
}

    /*
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
    */


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
        return;
    }
    // Print the path by tracing back through the 'path' array
    // path keeps track of the previous node on the shortest path to each node
    printPath(from, T[from][to].path);
    cout << data[to] << " ";
}