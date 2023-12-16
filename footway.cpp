/*footway.cpp*/

/// <sumary>
/// This file provides methods to operate on one footway
/// <summary>

// Import relevant files & libarries
#include "footway.h"
using namespace std;

// constructor
Footway::Footway(long long id)
  : ID(id)
{
  // constructor is empty because nothing needs to be initialized
  // vector is default initialized in cpp
}

// add node ID to end of vector
void Footway::add(long long nodeid) {
  this->NodeIDs.push_back(nodeid);
}

// determine if a particular footway intersects with the building's node IDs
bool Footway::check_node(Building& B) {
  for (long long node : this->NodeIDs) {
    if (B.find_footway_intersection(node)) {
      return true;
    }
  }
  return false;
}