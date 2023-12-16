/*buildings.cpp*/

/// <sumary>
/// This file provides methods to operate on a collection of buildings
/// <summary> 

// Import relevant files & libraries
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "buildings.h"
#include "building.h"
#include "osm.h"
#include "tinyxml2.h"
#include "footways.h"
using namespace std;
using namespace tinyxml2;


// Parse through document and read buildings
void Buildings::readMapBuildings(XMLDocument& xmldoc) {
  XMLElement* osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  // Parse the XML document way by way, looking for university buildings:
  XMLElement* way = osm->FirstChildElement("way");

  while (way != nullptr) {
    const XMLAttribute* attr = way->FindAttribute("id");
    assert(attr != nullptr);

    // Buildings
    if (osmContainsKeyValue(way, "building", "university")) {
      string name = osmGetKeyValue(way, "name");
      string streetAddr = osmGetKeyValue(way, "addr:housenumber") + " " + osmGetKeyValue(way, "addr:street");

      // Create building object
      long long id = attr->Int64Value();
      Building B(id, name, streetAddr);
      XMLElement* nd = way->FirstChildElement("nd");
      while (nd != nullptr) {
        const XMLAttribute* ndref = nd->FindAttribute("ref");
        assert(ndref != nullptr);
        long long id = ndref->Int64Value();
        B.add(id);
        nd = nd->NextSiblingElement("nd");
      }
      // Store building in vector
      this->MapBuildings.push_back(B);
    }
    way = way->NextSiblingElement("way");
  }
}

// Access data - number of buildings
int Buildings::getNumMapBuildings() {
  return (int) this->MapBuildings.size();
}

// Access data - print information about all buildings
void Buildings::print() {
  for (Building B : this->MapBuildings) {
    cout << B.ID << ": " << B.Name << ", " << B.StreetAddress << endl;
  }
}

// Access data - find relevant building
void Buildings::findAndPrint(string name, Nodes& nodes, Footways& F) {
  for (Building B : this->MapBuildings) {
    if (B.Name.find(name) != string::npos) {
      B.print(nodes);
      cout << "Footways that intersect:" << endl;
      F.print_get_intersection(B);
    }
  }
}