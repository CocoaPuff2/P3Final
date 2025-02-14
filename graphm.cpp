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
    size = 0;
    if (!input) {
        cout << "Input file not open or not valid!" << endl;
        return -1; // or any other error code
    }
    input >> size; // read # of nodes in graph
    input.ignore(); // debug line: ignore the newline
    cout << "size: " << size << endl;

    /*
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
        // store in Adjacency Matrix (AM)
        C[fromIndex][toIndex] = edgeCost;
    }
     */
    return 1;
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

Adjacency Matrix (AM)
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


 a: source
    ex: source = 1
     visited(1) = true
 b: v
    ex: v = 1
        c: j (adjacency)
            ex: j = 1: : dist(1-1) = 0  path(1-1)
            ex: j = 2: : dist(1-2) = 10  path(1-2)
            ex: j = 3: : dist(1-1) = 5  path(1-3)

    ex: v = 2:
         c: j (adjacency)
            ex: j = 1: : not adjacent
            ex: j = 2: : dist(2-2) = 0
            ex: j = 3: : dist(2-3) = 20  path(2-3)

    ex: v = 3:
         c: j (adjacency)
            ex: j = 1: : not adjacent
            ex: j = 2: : not adjacent
            ex: j = 3: : dist(3-3) = 0
 */

void GraphM::findShortestPath() {
    // loop through possible source nodes in graph
    // A: Source
    for (int source = 1; source <= size; source ++) {
        // reset table
        for (int i = 1; i <= size; i++) {
            T[source][i].dist = INT_MAX;
            T[source][i].visited = false;
            T[source][i].path = -1;
        }

        T[source][source].dist = 0; //  dist from source to source // 1 --> 1 =

        // B: V
        for (int v = 1; v <= size; v++) {
            // ex: [1][1] is visited and no adjacent nodes? cont.
            if (T[source][v].visited && C[source][v] == INT_MAX) {
                continue;
            }

            // ex: [1][1] mark visited
            T[source][v].visited = true;

            // C: J Adjacency Matrix
                for (int j = 1; j <= size; j++) {
                    // if no adjacent, cont.
                    if (C[v][j] == INT_MAX || v == j) {
                        continue;
                    }
                    // ex: [1][3].dist = min([1][3].dist, 20)
                    T[source][j].dist = min(T[source][j].dist,T[source][v].dist + C[v][j]);
                    // path = 1 3 (prev node)

                }
        }

    }
}

void GraphM::displayAll() const {
    // Iterate through all the nodes
    for (int from = 1; from <= size; ++from) {
        // Print the node's name at the beginning of each section
        // cout << left << setw(25) << data[from - 1] << endl;


        // Print  table header
        cout << left << setw(35) << "Description" << setw(15) << "From node"
             << setw(15) << "To node" << setw(15) << "Distance" << "Path" << endl;

        // Print the paths for the current node
        for (int to = 1; to <= size; ++to) {
            if (from == to) {
                continue;
            }

            // Print the node name, and details about the "from" and "to" nodes
            // data[from - 1]
            cout << left << setw(35) << data[from] << setw(15) << from
                 << setw(15) << to;

            // data[from - 1] and [to-1]
            if (T[from][to].dist == INT_MAX) {
                cout << "---" << setw(15) << endl;
            } else {
                cout << setw(15) << T[from][to].dist;
                // printPath(from - 1, to - 1);  // Print the path for this pair
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

    if (T[src][dest].dist == INT_MAX) {
        printPath(src, dest);
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
        cout << "---" << endl;  // no path exists
        return;
    }
    // Print the path by tracing back through the 'path' array
    // path keeps track of the previous node on the shortest path to each node
    cout << data[to] << " ";
    printPath(from, T[from][to].path);
}