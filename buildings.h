/*buildings.h*/

/// <sumary>
/// Header file for buildings.cpp
/// <summary> 

// Import relevant files & libraries
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "buildings.h"
#include "nodes.h"
#include "footways.h"
#include "osm.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

// Collection of building objects
class Buildings
{
public:
  vector<Building> MapBuildings;

  void readMapBuildings(XMLDocument& xmldoc);

  int getNumMapBuildings();

  void print();

  void findAndPrint(string name, Nodes& nodes, Footways& F);
};