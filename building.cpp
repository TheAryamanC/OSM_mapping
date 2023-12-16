/*building.cpp*/

/// <sumary>
/// This file provides methods to operate on one building
/// <summary>

// Import necessary files & libraries
#include <iostream>
#include "building.h"
using namespace std;

// constructor
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr) {
  // constructor is empty because nothing needs to be initialized
  // vector is default initialized in cpp
}

// add node ID to end of vector
void Building::add(long long nodeid) {
  this->NodeIDs.push_back(nodeid);
}

// print relevant information about building
//   this includes the name, address, location (latitude/longitude) and the nodes
void Building::print(Nodes& nodes) {
  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;
  double avgLat = this->getLocation(nodes).first;
  double avgLong = this->getLocation(nodes).second;
  cout << "Approximate Location: (" << avgLat << ", " << avgLong << ")" << endl;
  cout << "Nodes:" << endl;
  for (long long nodeid : this->NodeIDs) {
    cout << "  " << nodeid << ": ";
    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;
    bool found = nodes.find(nodeid, lat, lon, entrance);
    if (found) {
      cout << "(" << lat << ", " << lon << ")";
      if (entrance) {
        cout << ", is entrance";
      }
      cout << endl;
    }
    else {
      cout << "**NOT FOUND**" << endl;
    }
  }
}

// determine if a particular path intersects with the building's node IDs
bool Building::find_footway_intersection(long long id) {
  for (long long nodeid : this->NodeIDs) {
    if (id == nodeid) {
      return true;
    }
  }
  return false;
}

// determine the average position of a building from the latitude/longitude of its nodes
pair<double, double> Building::getLocation(Nodes& nodes) {
  double avgLat = 0;
  double avgLong = 0;
  for (size_t i = 0; i < this->NodeIDs.size(); i++) {
    long long node1 = this->NodeIDs[i];
    double lat1;
    double long1;
    bool isEnt1;
    nodes.find(node1, lat1, long1, isEnt1);
    avgLat += lat1;
    avgLong += long1;
  }
  avgLat = (double) avgLat / this->NodeIDs.size();
  avgLong = (double) avgLong / this->NodeIDs.size();
  return make_pair(avgLat, avgLong);
}