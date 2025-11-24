// COMSC-210 | Lab 34 | Diksha Tara Natesan
// IDE used: Vim/Terminal

// Application theme: Indoor Bouldering (Rock Climbing)  Problem (climbing beta exploration)
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

const int SIZE = 11; // nodes 0–10

struct Edge {
    int src, dest, weight; // weight = move difficulty
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    Graph(const vector<Edge> &edges) {
        adjList.resize(SIZE);
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // undirected graph
            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // DFS and BFS methods could still be here if needed for earlier steps,
    // but they are NOT called in main for this step.

    // Dijkstra's algorithm: shortest total weight from 'start' to all vertices
    void shortestPaths(int start) {
        const int INF = numeric_limits<int>::max();
        vector<int> dist(SIZE, INF);

        // min-heap priority queue: (currentDistance, node)
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;

        dist[start] = 0;
        pq.push(make_pair(0, start));

        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (currentDist > dist[u]) {
                continue;
            }

            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        cout << "Shortest path from node " << start << ":" << endl;
        for (int i = 0; i < SIZE; i++) {
            cout << start << " -> " << i << " : ";
            if (dist[i] == INF) {
                cout << "unreachable";
            } else {
                cout << dist[i];
            }
            cout << endl;
        }
    }
};

int main() {
    // Updated graph edges
    vector<Edge> edges = {
        {0, 2, 10},  // 0 <-> 2
        {0, 4, 7},   // 0 <-> 4
        {2, 4, 3},   // 2 <-> 4
        {2, 5, 8},   // 2 <-> 5
        {2, 6, 12},  // 2 <-> 6
        {4, 7, 4},   // 4 <-> 7
        {5, 8, 6},   // 5 <-> 8
        {6, 9, 5},   // 6 <-> 9
        {7,10, 9},   // 7 <-> 10
        {8, 9, 2},   // 8 <-> 9
        {9,10,11}    // 9 <-> 10
    };

    Graph g(edges);

    // For this step, ONLY print shortest paths:
    g.shortestPaths(0);

    return 0;
}
