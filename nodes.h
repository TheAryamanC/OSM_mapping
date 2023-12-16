/*nodes.h*/

/// <sumary>
/// Header file for nodes.cpp
/// <summary>

// Import relevant files & libraries
#pragma once
#include <vector>
#include <map>
#include "node.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

// Collection of node objects
class Nodes
{
private:
  map<long long, Node> MapNodes;

public:
  void readMapNodes(XMLDocument& xmldoc);

  void sortByID();

  bool find(long long id, double& lat, double& lon, bool& isEntrance);

  int getNumMapNodes();

  std::map<long long, Node>::iterator begin();
  std::map<long long, Node>::iterator end();
};