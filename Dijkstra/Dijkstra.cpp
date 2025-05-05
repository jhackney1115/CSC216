#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;

class Graph {
public:
    using Node = string;
    using Weight = int;
    using Neighbor = pair<Node, Weight>;
    using AdjacencyMap = unordered_map<Node, vector<Neighbor>>;
    using Edge = tuple<Node, Node, Weight>;

    // Constructor: directed or undirected graph
    Graph(bool undirected = false) : undirected(undirected) {}

    // Add an edge to the graph
    void addEdge(const Node& u, const Node& v, Weight w) {
        adjMap[u].push_back({v, w});
        nodes.insert(u);
        nodes.insert(v);
        if (undirected) {
            adjMap[v].push_back({u, w});
        }
    }

    // Load multiple edges from a vector of (u, v, w)
    void loadFromEdgeList(const vector<Edge>& edges) {
        for (const auto& [u, v, w] : edges) {
            addEdge(u, v, w);
        }
    }

    // Print the adjacency list
    void printGraph() const {
        cout << "Graph adjacency list:" << endl;
        for (const auto& [node, neighbors] : adjMap) {
            cout << "  " << node << "->";
            for (const auto& [neighbor, weight] : neighbors) {
                cout << "(" << neighbor << ", " << weight << ") ";
            }
            cout << endl;
        }
    }

    // Dijkstra's algorithm: returns distance, or optionally the full 
    // path
    pair<int, vector<Node>> dijkstra(const Node& start,
        const Node& end) const {
        // Priority queue: (distance, node)
        priority_queue<pair<int, Node>, vector<pair<int, Node>>, 
        greater<>> pq;

        // Distance map: initialize all distances to infinity
        unordered_map<Node, int> distances;
        unordered_map<Node, Node> previous;

        for (const auto& node : nodes) {
            distances[node] = numeric_limits<int>::max();
        }

        // Set starting node distance to 0 and push to queue
        distances[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [currentDist, currentNode] = pq.top();
            pq.pop();

            // If we reached the end node, stop search
            if (currentNode == end) break;

            // Skip if a shorter path to currentNode has been found
            if (currentDist > distances[currentNode]) continue;

            // Explore neighbors (if any)
            if (adjMap.count(currentNode)) {
                for (const auto& [neighbor, weight] : adjMap.at
                (currentNode)) {
                    int newDist = currentDist + weight;
                    if (newDist < distances[neighbor]) {
                        distances[neighbor] = newDist;
                        previous[neighbor] = currentNode;
                        pq.push({newDist, neighbor});
                    }
                }
            }
        }

        // If end node was not reached
        if (distances[end] == numeric_limits<int>::max()) {
            return {-1, {}};
        }

        // Reconstruct path
        vector<Node> path;
        for (Node at = end; at != start; at = previous[at]) {
            path.push_back(at);
        }
        path.push_back(start);
        reverse(path.begin(), path.end());

        return {distances[end], path};
    }

private:
    AdjacencyMap adjMap;
    unordered_set<Node> nodes;
    bool undirected;
};

// Example usage
int main() {
    // Create an undirected graph
    Graph g(true);

    // Load edges
    vector<Graph::Edge> edges = {
        {"A", "B", 4},
        {"A", "C", 2},
        {"B", "C", 5},
        {"B", "D", 10},
        {"C", "E", 3},
        {"E", "D", 4},
        {"D", "F", 11}
    };
    g.loadFromEdgeList(edges);

    // Print the graph
    g.printGraph();

    // Test: A to F
    auto [distance, path] = g.dijkstra("A", "F");
    if (distance != -1) {
        cout << "Shortest path length from A to F is: " << distance 
        << endl;
        cout << "Path: ";
        for (const auto& node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path exists from A to F." << endl;
    }

    // Test: B to A
    auto [distBA, pathBA] = g.dijkstra("B", "A");
    if (distBA != -1) {
        cout << "Shortest path length from B to A is: " << distBA 
        << endl;
        cout << "Path: ";
        for (const auto& node : pathBA) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path exists from B to A." << endl;
    }

    return 0;
}
