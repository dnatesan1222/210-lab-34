// COMSC-210 | Lab 34 | Diksha Tara Natesan
// IDE used: Vim/Terminal

// Application theme: Indoor Bouldering (Rock Climbing)  Problem (climbing beta exploration)
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

const int SIZE = 11; // nodes 0–10

struct Edge {
    int src, dest, weight; // weight = move difficulty
};

typedef pair<int, int> Pair;

// Names for each section of the bouldering problem
const string SECTION_NAMES[SIZE] = {
    "Start Holds",              // 0
    "Retired Hold Cluster A",   // 1 (unused in current problem)
    "First Crux",               // 2
    "Retired Hold Cluster B",   // 3 (unused in current problem)
    "High Step Ledge",          // 4
    "Sidepull Sequence",        // 5
    "Dyno Section",             // 6
    "Rest Jug",                 // 7
    "Undercling Rail",          // 8
    "Sloper Rail Near Top",     // 9
    "Top Jug Finish"            // 10
};

class Graph {
public:
    // adjacency list: for each section, list of (neighbor, difficulty)
    vector<vector<Pair>> adjList;

    // Graph constructor
    Graph(const vector<Edge> &edges) {
        adjList.resize(SIZE);
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // undirected bouldering moves (you can go back and forth)
            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the bouldering problem topology
    void printGraph() {
        cout << "Indoor Bouldering Problem Topology:" << endl;
        cout << "===================================" << endl;

        for (int i = 0; i < SIZE; i++) {
            if (adjList[i].empty()) {
                // skip completely unused sections (like retired hold clusters)
                continue;
            }

            cout << "Section " << i << " (" << SECTION_NAMES[i] << ") connects to:" << endl;
            for (auto &nbr : adjList[i]) {
                int next = nbr.first;
                int difficulty = nbr.second;
                cout << "  \u2192 Section " << next << " (" << SECTION_NAMES[next]
                     << ") - Move difficulty: " << difficulty << endl;
            }
        }
    }

    // DFS utility for recursive exploration
    void DFSUtil(int v, vector<bool> &visited) {
        visited[v] = true;
        cout << "Inspecting Section " << v << " (" << SECTION_NAMES[v] << ")" << endl;

        for (auto &neighbor : adjList[v]) {
            int next = neighbor.first;
            int difficulty = neighbor.second;

            if (!visited[next]) {
                cout << "  \u2192 Possible move to Section " << next << " ("
                     << SECTION_NAMES[next] << ") - Difficulty: " << difficulty << endl;
                DFSUtil(next, visited);
            }
        }
    }

    // DFS starting at a specific section
    void DFS(int start) {
        vector<bool> visited(SIZE, false);

        cout << endl;
        cout << "Route Exploration (DFS) from Section " << start
             << " (" << SECTION_NAMES[start] << "):" << endl;
        cout << "Purpose: Exploring all possible beta sequences a climber might try" << endl;
        cout << "=======================================" << endl;

        DFSUtil(start, visited);
    }

    // BFS starting at a specific section
    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << endl;
        cout << "Layer-by-Layer Beta Exploration (BFS) from Section " << start
             << " (" << SECTION_NAMES[start] << "):" << endl;
        cout << "Purpose: Understanding how many moves from the start each section is" << endl;
        cout << "=================================================" << endl;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            cout << "Checking Section " << v << " (" << SECTION_NAMES[v] << ")" << endl;

            for (auto &neighbor : adjList[v]) {
                int next = neighbor.first;
                int difficulty = neighbor.second;

                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                    cout << "  \u2192 Next move: Section " << next << " ("
                         << SECTION_NAMES[next] << ") - Difficulty: " << difficulty << endl;
                }
            }
        }
    }
};

int main() {
    // New graph for the bouldering problem
    vector<Edge> edges = {
        // (src, dest, difficulty)
        {0, 2, 10},  // Start Holds <-> First Crux
        {0, 4, 7},   // Start Holds <-> High Step Ledge
        {2, 4, 3},   // First Crux  <-> High Step Ledge
        {2, 5, 8},   // First Crux  <-> Sidepull Sequence
        {2, 6, 12},  // First Crux  <-> Dyno Section
        {4, 7, 4},   // High Step   <-> Rest Jug
        {5, 8, 6},   // Sidepull    <-> Undercling Rail
        {6, 9, 5},   // Dyno        <-> Sloper Rail Near Top
        {7,10, 9},   // Rest Jug    <-> Top Jug Finish
        {8, 9, 2},   // Undercling  <-> Sloper Rail Near Top
        {9,10,11}    // Sloper Rail <-> Top Jug Finish
    };

    Graph boulder(edges);
    boulder.printGraph();
    boulder.DFS(0);  // start from Start Holds
    boulder.BFS(0);  // same start section

    return 0;
}
