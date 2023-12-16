/*building.h*/

/// <sumary>
/// Header file for building.cpp
/// <summary>

// Import relevant files and libraries
#pragma once
#include <string>
#include <vector>
#include "node.h"
#include "nodes.h"
using namespace std;

// Building class definition
class Building
{
public:
  long long ID;
  string Name;
  string StreetAddress;
  vector<long long> NodeIDs;

  // constructor
  Building(long long id, string name, string streetAddr);

  void add(long long nodeid);

  void print(Nodes& nodes);

  bool find_footway_intersection(long long id);

  pair<double, double> getLocation(Nodes& nodes);
};
