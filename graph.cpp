//This is graph.cpp

#include "graph.h"

using namespace std;

int helper_found_function(string vertex, const map<string, int>& vertices_index) {
    auto result = vertices_index.find(vertex);
    if (result == vertices_index.end()) {
        return -1;
    }
    else {
        return result->second;
    }
}

graph::graph() {
    // constructor
    this->num_edges = 0;
}

int graph::NumVertices() const {
    // length of vector
    return this->vertices.size();
}

int graph::NumEdges() const {
    // private variable that gets updated if new edge is created
    return this->num_edges;
}

bool graph::addVertex(string v) {
    // find index
    int found = helper_found_function(v, this->vertices_index);
    // if v not in vertices
    if (found != -1) {
        return false;
    }
    // add to vertices
    this->vertices.push_back(v);
    // create its index
    this->vertices_index[v] = this->NumVertices() - 1;
    // create empty map for vertex (for edges)
    map<string, double> empty_map_for_v;
    this->edges.push_back(empty_map_for_v);
    return true;
}

bool graph::addEdge(string from, string to, double weight) {
    // find indexes of vertices
    int found_from = helper_found_function(from, this->vertices_index);
    int found_to = helper_found_function(to, this->vertices_index);
    // if either not found - exit & return false
    if (found_from == -1 || found_to == -1) {
        return false;
    }
    // if 'to' not in map of from, increment number of edges
    if (this->edges[found_from].find(to) == this->edges[found_from].end()) {
        this->num_edges += 1;
    }
    // set weight
    this->edges[found_from][to] = weight;
    return true;
}

bool graph::getWeight(string from, string to, double& weight) const {
    // find indexes of vertices
    int found_from = helper_found_function(from, this->vertices_index);
    int found_to = helper_found_function(to, this->vertices_index);
    // if either not found - exit & return false
    if (found_from == -1 || found_to == -1) {
        return false;
    }
    // get index
    int index = this->vertices_index.find(from)->second;
    // create copy of map (so actual map doesn't change)
    auto map_of_edges_from_from = this->edges[index];
    // if edge found, set weight parameter & return true
    if (map_of_edges_from_from.find(to) != map_of_edges_from_from.end()) {
        weight = map_of_edges_from_from.find(to)->second;
        return true;
    }
    return false;
}

set<string> graph::neighbors(string v) const {
    // create empty set
    set<string> neighbors;
    // find indexes of vertex
    int found_v = helper_found_function(v, this->vertices_index);
    // if not found, return empty set
    if (found_v == -1) {
        return neighbors;
    }
    // create copy of map corresponding to vertex
    auto map_of_neighbors = this->edges[found_v];
    // go through map & add edges to set
    for (auto p : map_of_neighbors) {
        neighbors.insert(p.first);
    }
    return neighbors;
}

vector<string> graph::getVertices() const {
    // returns vector of vertices
    return this->vertices;
}

void graph::print(ostream& output) const {
    // print basic info - number of vertices & edges
    cout << "This graph has: " << endl;
    cout << "  " << this->NumVertices() << " vertices" << endl;
    cout << "  " << this->NumEdges() << " edges" << endl;
    cout << endl;
    // for each vertex, print out connections to other vertices (if any)
    for (int i = 0; i < this->NumVertices(); i++) {
        string vrtx = this->getVertices()[i];
        if (!this->neighbors(vrtx).empty()) {
            cout << "  Vertex " << this->getVertices()[i] << " has edges to:" << endl;
            for (auto p : this->edges[i]) {
                cout << "    " << p.first << " with a weight of " << p.second << endl;
            }
        }
        else {
            cout << "  Vertex " << vrtx << " has no edges" << endl;
        }
    }
}