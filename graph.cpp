// COMSC-210 | Lab 34 | Diksha Tara Natesan
// IDE used: Vim/Terminal

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 7;

struct Edge {
    int src, dest, weight;
};

typedef pair<int,int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);
        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjList[src].push_back(make_pair(dest, weight));
            adjList[dest].push_back(make_pair(src, weight)); // undirected
        }
    }

    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    void DFSUtil(int v, vector<bool> &visited) {
        visited[v] = true;
        cout << v << " ";

        for (auto &neighbor : adjList[v]) {
            int next = neighbor.first;
            if (!visited[next]) {
                DFSUtil(next, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        cout << "DFS starting from vertex " << start << ":" << endl;
        DFSUtil(start, visited);
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from vertex " << start << ":" << endl;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (auto &neighbor : adjList[v]) {
                int next = neighbor.first;
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    vector<Edge> edges = {
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };

    Graph graph(edges);
    graph.printGraph();

    graph.DFS(0);
    graph.BFS(0);

    return 0;
}

