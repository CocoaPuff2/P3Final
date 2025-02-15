#include "graphm.h"
#include <fstream>
#include <iomanip>
#include <climits>
#include <queue>

using namespace std;


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
    input >> size;
    if (size <= 0 || size >= MAXNODES) return -1;

    input.ignore(numeric_limits<streamsize>::max(), '\n');


    for (int i = 1; i <= size; i++) {
        if (!getline(input >> ws, data[i])) return -1;
        if (!data[i].empty() && data[i].back() == '\r') {
            data[i].pop_back();
        }
    }

    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            C[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }

    int from, to, cost;
    while (input >> from >> to >> cost) {
        if (from == 0) break;
        C[from][to] = cost;
    }

    // Print the full C table
    /*
    cout << "Cost Matrix C:" << endl;
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= size; j++) {
            if (C[i][j] == INT_MAX)
                cout << setw(5) << "∞";  // Display infinity for unreachable paths
            else
                cout << setw(5) << C[i][j];
        }
        cout << endl;
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

int GraphM::findV(int source) {
    int minDist = INT_MAX;
    int minIndex = -1;

    for (int i = 1; i <= size; i++) {
        // if unvisited node v and distance is smaller than currnet minDist
        if (!T[source][i].visited && T[source][i].dist < minDist){
            minDist = T[source][i].dist;
            minIndex = i;
        }
    }
    return minIndex;

}

void GraphM::findShortestPath() {
    // loop through possible source nodes in graph
    // A: Source
    for (int source = 1; source <= size; source ++) {
         // cout << "\nProcessing source node: " << source << endl;
        // reset table
        for (int i = 1; i <= size; i++) {
            T[source][i].dist = INT_MAX;
            T[source][i].visited = false;
            T[source][i].path = -1;
        }

        T[source][source].dist = 0; //  dist from source to source // 1 --> 1 = 0

        // B: V
        for (int v = 1; v <= size; v++) {

            // ex: [1][1] is visited and no adjacent nodes? cont.
                // utility function: go thru t table, find first v that is not visited, save that as min dist,
                // when done with the loop, then you have the min dist and store the index as well
                // so you know that the node at index, (3) for example,  has the shortest distance from the
                // source, (1) for example,  with the min dist 20 for example
                int minV = findV(source);
                if (minV <= 0) {
                    break;
                }

            T[source][minV].visited = true;
            if (T[source][minV].dist == INT_MAX) {
                T[source][minV].dist =  C[source][minV];
            }
             // cout << "Visiting node " << minV << " from source " << source << endl;

            // C: J Adjacency Matrix
                for (int j = 1; j <= size; j++) {
                    // if no adjacent, cont.
                    if (C[minV][j] == INT_MAX) {
                        continue;
                    }

                   //  cout << "Updating distance for node " << j << " from source " << source
                         // << ": " << T[source][j].dist << " -> " << T[source][minV].dist + C[minV][j] << endl;
                   //  T[source][j].dist = min(T[source][j].dist, T[source][minV].dist + C[minV][j]);
                    if (T[source][minV].dist + C[minV][j] < T[source][j].dist) {
                        T[source][j].dist = T[source][minV].dist + C[minV][j];
                        T[source][j].path = minV;  // store prev node in shortest path
                    }
                }
        }

    }
}

void GraphM::displayAll() const {
    // Iterate through all the nodes
    for (int from = 1; from <= size; ++from) {
        // Table header
        if (from == 1) {
            cout << left << setw(35) << "Description" << setw(15) << "From node"
                 << setw(15) << "To node" << setw(15) << "Distance" << "Path" << endl;
        }

        // node name
        cout << left << setw(35) << data[from];

        // Paths for the current node
        bool first = true;
        for (int to = 1; to <= size; ++to) {
            if (from == to) {
                continue;
            }

           if (first) {
               cout << setw(15) << from
                    << setw(15) << to;
               first = false;
           } else {
               cout << setw(35) << ""
                    << setw(15) << from
                    << setw(15) << to;
           }

            // Check if distance is not infinite
            if (T[from][to].dist == INT_MAX) {
                cout << "---" << setw(15);
                cout << endl;
            } else {
                cout << setw(15) << T[from][to].dist;
                printPath(from, to);
                cout << endl;
            }
        }
        cout << endl;
    }
}


void GraphM::display(int from, int to) const {
    if (T[from][to].dist == INT_MAX) {
        cout << setw(8) << " " << setw(8) << from << setw(8) << to << setw(8) << "---" << endl;
        return;
    }
    cout << setw(8) << " " << setw(8) << from << setw(8) << to << setw(8) << T[from][to].dist << "    ";
    printPath(from, to);
    cout << endl;
    printPathNames(from, to);
    cout << endl;

}

void GraphM::printPathNames(int from, int to) const {
    vector <int> path;
    int curr = to;

    while (curr != from) {
        path.push_back(curr);
        curr = T[from][curr].path;
    }
    path.push_back(from);

    for (int i = path.size() - 1; i >= 0; --i) {
        cout << data[path[i]] << endl;
    }
}



void GraphM::printPath(int from, int to) const {
    if (T[from][to].path == -1) {
        return;  // no valid path
    }

    vector<int> path;
    int curr = to;

    //  path from `to` to `from`
    while (curr != from) {
        path.push_back(curr);
        curr = T[from][curr].path;
    }
    path.push_back(from);  // push source node

    // Print path correct order
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << path[i] << " ";
    }
}

int GraphM::insertEdge(int from, int to, int cost) {
    // Check if the nodes are valid
    if (from < 1 || from > size || to < 1 || to > size) {
        std::cout << "Error: Invalid nodes for edge insertion!" << std::endl;
        return -1;  // Return -1 to indicate failure
    }

    // Insert the edge into the graph (set the cost)
    C[from][to] = cost;
    return 1;
}

int GraphM::removeEdge(int from, int to) {
    // Check if the nodes are valid
    if (from < 1 || from > size || to < 1 || to > size) {
        std::cout << "Error: Invalid nodes for edge removal!" << std::endl;
        return -1;  // Return -1 to indicate failure
    }

    // Remove the edge (set the cost to 0 or another default value)
    C[from][to] = 0;
    return 1;
}
