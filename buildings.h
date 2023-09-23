/*buildings.h*/

//
// A collection of buildings in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

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


//
// Keeps track of all the buildings in the map.
//
class Buildings
{
public:
  vector<Building> MapBuildings;

  //
  // readMapBuildings
  //
  // Given an XML document, reads through the document and 
  // stores all the buildings into the given vector.
  //
  void readMapBuildings(XMLDocument& xmldoc);

  //
  // accessors / getters
  //
  int getNumMapBuildings();

  void print();

  void findAndPrint(string name, Nodes& nodes, Footways& F);
};