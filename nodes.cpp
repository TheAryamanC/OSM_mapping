/*nodes.cpp*/

/// <sumary>
/// This file provides methods to operate on a collection of nodes
/// <summary>

// Import relevant files & libraries
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <utility>
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

// Parse through document and read nodes
void Nodes::readMapNodes(XMLDocument& xmldoc)
{
  XMLElement* osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  // Parse the XML document node by node
  XMLElement* node = osm->FirstChildElement("node");

  while (node != nullptr)
  {
    const XMLAttribute* attrId = node->FindAttribute("id");
    const XMLAttribute* attrLat = node->FindAttribute("lat");
    const XMLAttribute* attrLon = node->FindAttribute("lon");

    assert(attrId != nullptr);
    assert(attrLat != nullptr);
    assert(attrLon != nullptr);

    long long id = attrId->Int64Value();
    double latitude = attrLat->DoubleValue();
    double longitude = attrLon->DoubleValue();

    // Check for entrance
    bool entrance = false;

    if (osmContainsKeyValue(node, "entrance", "yes") ||
      osmContainsKeyValue(node, "entrance", "main") ||
      osmContainsKeyValue(node, "entrance", "entrance"))
    {
      entrance = true;
    }

    // Store node in vector
    this->MapNodes.emplace(id, Node(id, latitude, longitude, entrance));  
    node = node->NextSiblingElement("node");
  }
}

// find specific node
bool Nodes::find(long long id, double& lat, double& lon, bool& isEntrance) {
  auto ptr = this->MapNodes.find(id);
  if (ptr == this->MapNodes.end()) {
    return false;
  }
  else {
    lat = ptr->second.getLat();
    lon = ptr->second.getLon();
    isEntrance = ptr->second.getIsEntrance();
    return true;
  }
}

// Access data - number of nodes
int Nodes::getNumMapNodes() {
  return (int) this->MapNodes.size();
}

// Access data - first and last items in collection of nodes
std::map<long long, Node>::iterator Nodes::begin() {
  return this->MapNodes.begin();
}
std::map<long long, Node>::iterator Nodes::end() {
  return this->MapNodes.end();
}