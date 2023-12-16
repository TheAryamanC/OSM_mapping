/*graph.cpp*/

/// <summary>
/// This file provides methods to operate on a graph
/// <summary>

// Import relevant files & libraries
#include "graph.h"
using namespace std;

// Helper function - find a vertex from a map
int helper_found_function(long long vertex, const map<long long, int>& vertices_index) {
    auto result = vertices_index.find(vertex);
    if (result == vertices_index.end()) {
        return -1;
    }
    else {
        return result->second;
    }
}

// constructor
graph::graph() {
    this->EdgeCount = 0;
}

// number of vertices in graph
int graph::NumVertices() const {
    return this->Vertices.size();
}

// number of edges in graph
int graph::NumEdges() const {
    return this->EdgeCount;
}

// add vertex to graph
bool graph::addVertex(long long v) {
    int found = helper_found_function(v, this->Vertex2Index);
    // if vertex is already in map, no need to add again
    if (found != -1) {
        return false;
    }
    // add vertex & create map corresponding to edges
    this->Vertices.push_back(v);
    this->Vertex2Index[v] = this->NumVertices() - 1;
    map<int, double> empty_map_for_v;
    this->Edges.push_back(empty_map_for_v);
    return true;
}

// add edge to graph
bool graph::addEdge(long long from, long long to, double weight) {
    int found_from = helper_found_function(from, this->Vertex2Index);
    int found_to = helper_found_function(to, this->Vertex2Index);
    // if either vertex is not in graph, cannot create edge
    if (found_from == -1 || found_to == -1) {
        return false;
    }
    if (this->Edges[found_from].find(to) == this->Edges[found_from].end()) {
        this->EdgeCount += 1;
    }
    this->Edges[found_from][to] = weight;
    return true;
}

// get weight of edge
bool graph::getWeight(long long from, long long to, double& weight) const {
    int found_from = helper_found_function(from, this->Vertex2Index);
    int found_to = helper_found_function(to, this->Vertex2Index);
    // if either vertex is not in graph, cannot retrieve weight
    if (found_from == -1 || found_to == -1) {
        return false;
    }

    int index = this->Vertex2Index.find(from)->second;
    auto map_of_edges_from_from = this->Edges[index];
    // ensure vertices are different
    if (map_of_edges_from_from.find(to) != map_of_edges_from_from.end()) {
        weight = map_of_edges_from_from.find(to)->second;
        return true;
    }
    return false;
}

// retrieve all neighbors of a given vertex
set<long long> graph::neighbors(long long v) const {
    set<long long> neighbors;
    int found_v = helper_found_function(v, this->Vertex2Index);
    if (found_v == -1) {
        return neighbors;
    }
    auto map_of_neighbors = this->Edges[found_v];
    for (auto p : map_of_neighbors) {
        neighbors.insert(p.first);
    }
    return neighbors;
}

// all vertices of graph
vector<long long> graph::getVertices() const {
    // returns vector of vertices
    return this->Vertices;
}

// information about graph
void graph::print(ostream& output) const {
    // number of vertices & edges
    cout << "This graph has: " << endl;
    cout << "  " << this->NumVertices() << " vertices" << endl;
    cout << "  " << this->NumEdges() << " edges" << endl;
    cout << endl;
    // edges to other vertices (if any)
    for (int i = 0; i < this->NumVertices(); i++) {
        long long vrtx = this->getVertices()[i];
        if (!this->neighbors(vrtx).empty()) {
            cout << "  Vertex " << this->getVertices()[i] << " has edges to:" << endl;
            for (auto p : this->Edges[i]) {
                cout << "    " << p.first << " with a weight of " << p.second << endl;
            }
        }
        else {
            cout << "  Vertex " << vrtx << " has no edges" << endl;
        }
    }
}