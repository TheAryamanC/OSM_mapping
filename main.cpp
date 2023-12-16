/*main.cpp*/

/// <sumary>
/// Main file
/// <summary>

// Import relevant files & libraries
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include "building.h"
#include "buildings.h"
#include "dist.h"
#include "footway.h"
#include "footways.h"
#include "graph.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

// Helper function - add vertices to graph
void add_vertices(Nodes& nodes, graph& g) {
  for (auto& n : nodes) {
    g.addVertex(n.second.getID());
  }
}

// Helper function - create edges to add to graph weighted by distance
void add_footway_edges(Footway& footway, graph& g, Nodes& nodes) {
  for (size_t i = 1; i < footway.NodeIDs.size(); i++) {
    long long node1 = footway.NodeIDs[i-1];
    double lat1;
    double long1;
    bool isEnt1;
    nodes.find(node1, lat1, long1, isEnt1);
    long long node2 = footway.NodeIDs[i];
    double lat2;
    double long2;
    bool isEnt2;
    nodes.find(node2, lat2, long2, isEnt2);
    g.addEdge(node1, node2, distBetween2Points(lat1, long1, lat2, long2));
    g.addEdge(node2, node1, distBetween2Points(lat2, long2, lat1, long1));
  }
}

// Helper function - add edge to graph
void add_edges(Footways& footways, graph& g, Nodes& nodes) {
  for (Footway f : footways.MapFootways) {
    add_footway_edges(f, g, nodes);
  }
}

// Class defining how priority queue should order items - in this case, will be by distance
class prioritize
{
public:
   bool operator() (const pair<long long,double>& p1, const pair<long long,double>& p2) const
   {
      if (p1.second > p2.second) {
        return true;
      }
      else if (p1.second < p2.second) {
        return false;
      }
      else {
        return p1.first > p2.second;
      }
   }
};

// Helper function - Dijstra's shortest pathfinding algorithm
vector<long long> Dijkstra(graph& G, long long startV, map<long long, double>& distances, map<long long, long long>& predecessors) {
  constexpr double INF = numeric_limits<double>::max();
  // Keep track of visited queue
  vector<long long>  visited;
  // Priority queue to determine which node to visit next
  priority_queue<pair<long long, double>, vector<pair<long long, double>>, prioritize> unvisitedQueue;
  // Keep track of which nodes are visited
  set<long long> visited_check;
  // Set all distances of other vertices to infinite, initialize predecessor and push into priority queue
  for (long long v : G.getVertices()) {
    if (v != startV) {
      distances[v] = INF;
      unvisitedQueue.push(make_pair(v, distances[v]));
      predecessors[v] = -1;
    }
  }
  // Set start vertex distance, set predecessor and push into priority queue
  distances[startV] = 0;
  unvisitedQueue.push(make_pair(startV, distances[startV]));
  predecessors[startV] = -1;
  
  // Repeat until all vertices are visited and shortest distances are calculated
  while (unvisitedQueue.size() != 0) {
    // Get first element in priority queue
    auto cV = unvisitedQueue.top();
    long long currentV = cV.first;
    unvisitedQueue.pop();
    
    // If distance to vertex is infinite, we know all vertices are unreachable
    if (distances[currentV] == INF) {
      break;
    }
    // If vertex is already visited, try next vertex
    else if (visited_check.count(currentV) > 0) {
      continue;
    }
    // Otherwise, visit the vertex
    else {
      visited.push_back(currentV);
      visited_check.insert(currentV);
    }
    // Visit all vertex neighbors
    set<long long> neighbors = G.neighbors(currentV);
    // Compare new distances and update as necessary
    for (long long n_v : neighbors) {
      double weight;
      G.getWeight(currentV, n_v, weight);
      double alt_weight = distances[currentV] + weight;
      
      if (alt_weight < distances[n_v]) {
        distances[n_v] = alt_weight;
        unvisitedQueue.push(make_pair(n_v, alt_weight));
        predecessors[n_v] = currentV;
      }
    }
  }
  // All vertices visited
  return visited;
}

// Helper function - find shortest path between two buildings
void navigate(Buildings& buildings, Nodes& nodes, Footways& footways, graph& g) {
  constexpr double INF = numeric_limits<double>::max();
  // Get first building
  cout << "Enter start building name (partial or complete)>" << endl;
  string name1;
  getline(cin, name1);

  Building startB(0, "", "");
  for (Building B : buildings.MapBuildings) {
    if (B.Name.find(name1) != string::npos) {
      startB = B;
      break;
    }
  }

  if (startB.ID == 0) {
    cout << "**Start building not found" << endl;
    return;
  }
  cout << "  Name: " << startB.Name << endl;
  double latS = startB.getLocation(nodes).first;
  double lonS = startB.getLocation(nodes).second;
  cout << "  Approximate Location: (" << latS << ", " << lonS << ")" << endl;
  double min_distS = INF;
  long long FOOTWAYIDS;
  long long NODEIDS;
  for (Footway f : footways.MapFootways) {
    for (size_t i = 0; i < f.NodeIDs.size(); i++) {
      long long nodeStart = f.NodeIDs[i];
      double latStart;
      double longStart;
      bool isEntS;
      nodes.find(nodeStart, latStart, longStart, isEntS);
      double distStart = distBetween2Points(latS, lonS, latStart, longStart);
      if (distStart < min_distS) {
        min_distS = distStart;
        FOOTWAYIDS = f.ID;
        NODEIDS = nodeStart;
      }
    }
  }
  cout << "  Closest footway ID " << FOOTWAYIDS << ", node ID " << NODEIDS << ", distance " << min_distS << endl;

  // Get second building
  cout << "Enter destination building name (partial or complete)>" << endl;
  string name2;
  getline(cin, name2);

  Building endB(0, "", "");
  for (Building B : buildings.MapBuildings) {
    if (B.Name.find(name2) != string::npos) {
      endB = B;
      break;
    }
  }

  if (endB.ID == 0) {
    cout << "**Destination building not found" << endl;
    return;
  }
  cout << "  Name: " << endB.Name << endl;
  double latD = endB.getLocation(nodes).first;
  double lonD = endB.getLocation(nodes).second;
  cout << "  Approximate Location: (" << latD << ", " << lonD << ")" << endl;
  double min_distD = INF;
  long long FOOTWAYIDD;
  long long NODEIDD;
  for (Footway f : footways.MapFootways) {
    for (size_t i = 0; i < f.NodeIDs.size(); i++) {
      long long nodeDest = f.NodeIDs[i];
      double latDest;
      double longDest;
      bool isEntD;
      nodes.find(nodeDest, latDest, longDest, isEntD);
      double distDest = distBetween2Points(latD, lonD, latDest, longDest);

      if (distDest < min_distD) {
        min_distD = distDest;
        FOOTWAYIDD = f.ID;
        NODEIDD = nodeDest;
      }
    }
  }
  cout << "  Closest footway ID " << FOOTWAYIDD << ", node ID " << NODEIDD << ", distance " << min_distD << endl;

  // Using Dijstra's to find the shortest path from first to second building
  long long startV = NODEIDS;
  map<long long, double> distances;
  map<long long, long long> predecessors;
  auto dijkstra_nodes = Dijkstra(g, startV, distances, predecessors);
  cout << "Shortest weighted path:" << endl;
  long long DestV = NODEIDD;

  // If distance to second building is infinite, it is unreachable 
  if (distances[DestV] == INF) {
    cout << "**Sorry, destination unreachable" << endl;
    return;
  }
  cout << "  # nodes visited: " << dijkstra_nodes.size() << endl;
  cout << "  Distance: " << distances[DestV] << " miles" << endl;
  cout << "  Path: ";

  // Create path between buildings using predecessors
  stack<long long> path;
  auto vertex = NODEIDD;
  path.push(vertex);
  while (predecessors[vertex] != -1) {
    path.push(predecessors[vertex]);
    vertex = predecessors[vertex];
  }
  // Print path
  while (!path.empty()) {
    cout << path.top();
    path.pop();
    if (path.size() > 0) {
      cout << "->";
    }
  }
  cout << endl;
}

// Main
int main() {
  cout << setprecision(12);
  XMLDocument xmldoc;
  Nodes nodes;
  Buildings buildings;
  Footways footways;
  graph G;
  
  cout << "** Open Street Map (University) **" << endl;

  string filename;
  cout << endl;
  cout << "Enter map filename> " << endl;
  getline(cin, filename);

  // If loading XML-based map failed - exit program
  if (!osmLoadMapFile(filename, xmldoc)) {
    return 0;
  }
  
  // Read nodes
  nodes.readMapNodes(xmldoc);

  // Read university buildings
  buildings.readMapBuildings(xmldoc);

  // Read footways
  footways.readMapFootways(xmldoc);

  // Create graph
  add_vertices(nodes, G);
  add_edges(footways, G, nodes);

  // Print important stats about map
  cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
  cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
  cout << "# of footways: " << footways.getNumMapFootways() << endl;
  cout << "# of graph vertices: " << G.NumVertices() << endl;
  cout << "# of graph edges: " << G.NumEdges() << endl;

  // User options
  while (true) {
    string name;
    cout << endl;
    cout << "Enter building name, * to list, @ to navigate, or $ to end> " << endl;
    getline(cin, name);

    // Break out of loop and end program
    if (name == "$") {
      break;
    }
    // List all buildings
    else if (name == "*") {
      buildings.print();
    }
    // Open navigation tool - find shortest path between buildings
    else if (name == "@") {
      navigate(buildings, nodes, footways, G);
    }
    // Display important information about building
    else {
      buildings.findAndPrint(name, nodes, footways); 
    }
  }

  // Display statistics about operations performed (for optimization purposes)
  cout << endl;
  cout << "** Done  **" << endl;
  cout << "# of calls to getID(): " << Node::getCallsToGetID() << endl;
  cout << "# of Nodes created: " << Node::getCreated() << endl;
  cout << "# of Nodes copied: " << Node::getCopied() << endl;
  cout << endl;

  return 0;
}