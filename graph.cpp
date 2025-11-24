// COMSC-210 | Lab 34 | Diksha Tara Natesan
// IDE used: Vim/Terminal

// Application theme: Indoor Bouldering (Rock Climbing)  Problem (climbing beta exploration)
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

const int SIZE = 11;

// --------------------------------------------------
// Edge structure
// --------------------------------------------------
struct Edge {
	int src, dest, weight;
};

typedef pair<int, int> Pair;

// --------------------------------------------------
// Graph class
// --------------------------------------------------
class Graph {
	public:
		vector<vector<Pair>> adjList;

		Graph(const vector<Edge> &edges) {
			adjList.resize(SIZE);
			for (auto &edge : edges) {
				adjList[edge.src].push_back(make_pair(edge.dest, edge.weight));
				adjList[edge.dest].push_back(make_pair(edge.src, edge.weight));
			}
		}

		// --------------------------
		// Display adjacency list
		// --------------------------
		void printGraph() {
			cout << "\nGraph adjacency list:\n";
			cout << "======================\n";

			for (int i = 0; i < SIZE; i++) {
				if (adjList[i].empty()) continue;

				cout << i << " -> ";
				for (auto &nbr : adjList[i]) {
					cout << "(" << nbr.first << ", " << nbr.second << ") ";
				}
				cout << endl;
			}
		}

		// --------------------------
		// DFS Utility
		// --------------------------
		void DFSUtil(int v, vector<bool> &visited) {
			visited[v] = true;
			cout << v << " ";

			for (auto &neighbor : adjList[v]) {
				int next = neighbor.first;
				if (!visited[next]) DFSUtil(next, visited);
			}
		}

		// --------------------------
		// DFS
		// --------------------------
		void DFS(int start) {
			vector<bool> visited(SIZE, false);

			cout << "\nDFS starting from " << start << ":\n";
			DFSUtil(start, visited);
			cout << endl;
		}

		// --------------------------
		// BFS
		// --------------------------
		void BFS(int start) {
			vector<bool> visited(SIZE, false);
			queue<int> q;

			visited[start] = true;
			q.push(start);

			cout << "\nBFS starting from " << start << ":\n";

			while (!q.empty()) {
				int v = q.front();
				q.pop();
				cout << v << " ";

				for (auto &nbr : adjList[v]) {
					int next = nbr.first;
					if (!visited[next]) {
						visited[next] = true;
						q.push(next);
					}
				}
			}
			cout << endl;
		}

		// --------------------------
		// Shortest Paths (Dijkstra)
		// --------------------------
		void shortestPaths(int start) {
			const int INF = numeric_limits<int>::max();
			vector<int> dist(SIZE, INF);

			priority_queue<Pair, vector<Pair>, greater<Pair>> pq;

			dist[start] = 0;
			pq.push(make_pair(0, start));

			while (!pq.empty()) {
				int currentDist = pq.top().first;
				int u = pq.top().second;
				pq.pop();

				if (currentDist > dist[u]) continue;

				for (auto &neighbor : adjList[u]) {
					int v = neighbor.first;
					int weight = neighbor.second;

					if (dist[v] > dist[u] + weight) {
						dist[v] = dist[u] + weight;
						pq.push(make_pair(dist[v], v));
					}
				}
			}

			cout << "\nShortest path from node " << start << ":\n";
			for (int i = 0; i < SIZE; i++) {
				cout << start << " -> " << i << " : ";
				if (dist[i] == INF) cout << "unreachable";
				else cout << dist[i];
				cout << endl;
			}
		}

		// --------------------------
		// Minimum Spanning Tree (Prim)
		// --------------------------
		void minimumSpanningTree() {
			const int INF = numeric_limits<int>::max();

			vector<int> key(SIZE, INF);
			vector<int> parent(SIZE, -1);
			vector<bool> inMST(SIZE, false);

			key[0] = 0;

			for (int count = 0; count < SIZE - 1; count++) {
				int u = -1;
				int minKey = INF;

				for (int i = 0; i < SIZE; i++) {
					if (!inMST[i] && key[i] < minKey) {
						minKey = key[i];
						u = i;
					}
				}

				if (u == -1) break;

				inMST[u] = true;

				for (auto &nbr : adjList[u]) {
					int v = nbr.first;
					int weight = nbr.second;

					if (!inMST[v] && weight < key[v]) {
						key[v] = weight;
						parent[v] = u;
					}
				}
			}

			cout << "\nMinimum Spanning Tree edges:\n";
			for (int i = 0; i < SIZE; i++) {
				if (parent[i] != -1) {
					cout << "Edge from " << parent[i] << " to " << i
						<< " with capacity: " << key[i] << " units\n";
				}
			}
		}
};

// --------------------------------------------------
// MAIN MENU
// --------------------------------------------------
int main() {
	vector<Edge> edges = {
		{0, 2, 10},
		{0, 4, 7},
		{2, 4, 3},
		{2, 5, 8},
		{2, 6, 12},
		{4, 7, 4},
		{5, 8, 6},
		{6, 9, 5},
		{7,10, 9},
		{8, 9, 2},
		{9,10,11}
	};

	Graph g(edges);

	int choice;

	do {
		cout << "\nBouldering Route Network Menu:\n";
		cout << "[1] Display bouldering network\n";
		cout << "[2] Explore possible moves (BFS)\n";
		cout << "[3] Explore all beta sequences (DFS)\n";
		cout << "[4] Calculate shortest paths\n";
		cout << "[5] Find Minimum Spanning Tree\n";
		cout << "[0] Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
			case 1: g.printGraph(); break;
			case 2: g.BFS(0); break;
			case 3: g.DFS(0); break;
			case 4: g.shortestPaths(0); break;
			case 5: g.minimumSpanningTree(); break;
			case 0: cout << "Exiting...\n"; break;
			default: cout << "Invalid choice.\n";
		}

	} while (choice != 0);

	return 0;
}
