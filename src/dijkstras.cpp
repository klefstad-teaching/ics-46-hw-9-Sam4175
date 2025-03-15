#include "dijkstras.h"
#include <algorithm>  // for std::reverse

// Struct to store distance and vertex in the priority queue
struct Node {
    int vertex;
    int dist;
    Node(int v, int d) : vertex(v), dist(d) {}
};

struct CompareDist {
    bool operator()(const Node& a, const Node& b) const {
        return a.dist > b.dist;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> dist(n, INF);        // Track the shortest distance to each vertex
    vector<bool> visited(n, false);  // Whether we've permanently set the distance to a vertex

    dist[source] = 0;
    previous.assign(n, -1);

    priority_queue<Node, vector<Node>, CompareDist> pq;  // Min-heap priority queue
    pq.push(Node(source, 0));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;

        // If already visited this node then skip
        if (visited[u]) continue;
        visited[u] = true;

        // Relax edges from u
        for (auto& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            // If a shorter path to v is found
            if (!visited[v] && dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                previous[v] = u;
                pq.push(Node(v, dist[v]));
            }
        }
    }

    return dist;  // Contains the shortest distances from 'source' to each vertex
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;
    int curr = destination;

    // Follow the chain of predecessors from destination back to the source
    while (curr != -1) {
        path.push_back(curr);
        curr = previous[curr];
    }

    // The path is currently reversed (from destination to source), so reverse it
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << "\n";
    } else {
        for (size_t i = 0; i < v.size(); ++i) {
            if (i > 0) cout << " ";

            cout << v[i];
        }
        cout << " " << endl;
    }
    cout << "Total cost is " << total << endl;
}
