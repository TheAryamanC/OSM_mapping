/*footway.h*/

/// <sumary>
/// Header file for footway.cpp
/// <summary>

// Import relevant files & libraries
#pragma once
#include <vector>
#include "building.h"
using namespace std;

// footway class definition
class Footway
{
public:
  long long ID;
  vector<long long> NodeIDs;

  // constructor
  Footway(long long id);
  
  void add(long long nodeid);

  bool check_node(Building& B);
};
