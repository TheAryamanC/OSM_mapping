/*node.cpp*/

/// <sumary>
/// This file provides methods to operate on nodes
/// <summary>

// Import relevant files & libraries
#include "node.h"
using namespace std;

// constructor
Node::Node(long long id, double lat, double lon, bool entrance)
  : ID(id), Lat(lat), Lon(lon), IsEntrance(entrance)
{
  Node::Created++;
}

// Copy constructor
Node::Node(const Node& other)
{
  this->ID = other.ID;
  this->Lat = other.Lat;
  this->Lon = other.Lon;
  this->IsEntrance = other.IsEntrance;
  Node::Copied++;
}

// Access data - get node ID
long long Node::getID() {
  Node::CallsToGetID++;
  return this->ID;
}

// Access data - get latitude
double Node::getLat() const {
  return this->Lat;
}

// Access data - get longitude
double Node::getLon() const {
  return this->Lon;
}

// Access data - determine if node is entry to building
bool Node::getIsEntrance() const {
  return this->IsEntrance;
}

// Access data - number of calls to get ID
int Node::getCallsToGetID() {
  return Node::CallsToGetID;
}

// Access data - number of nodes created
int Node::getCreated() {
  return Node::Created;
}

// Access data - number of nodes copied
int Node::getCopied() {
  return Node::Copied;
}