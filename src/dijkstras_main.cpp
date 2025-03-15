#include "dijkstras.cpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    string filename = (argc > 1) ? argv[1] : "src/small.txt";
    Graph G;
    file_to_graph(filename, G);

    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    cout << "Shortest Paths from " << source << ":" << endl;
    for (int destination = 0; destination < G.numVertices; ++destination) {
        vector<int> path = extract_shortest_path(distances, previous, destination);
        print_path(path, distances[destination]);
    }
    
    return 0;
}
