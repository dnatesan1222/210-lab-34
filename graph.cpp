// COMSC-210 | Lab 34 | Diksha Tara Natesan
// IDE used: Vim/Terminal

// Application theme: Indoor Bouldering (Rock Climbing)  Problem (climbing beta exploration)
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

const int SIZE = 11;

struct Edge {
	int src, dest, weight;
};

typedef pair<int, int> Pair;

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

			cout << "Minimum Spanning Tree edges:" << endl;
			for (int i = 0; i < SIZE; i++) {
				if (parent[i] != -1) {
					cout << "Edge from " << parent[i] << " to " << i
						<< " with capacity: " << key[i] << " units" << endl;
				}
			}
		}
};

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
	g.minimumSpanningTree();

	return 0;
}
