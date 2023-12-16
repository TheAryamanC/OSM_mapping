/*osm.cpp*/

/// <sumary>
/// This file provides methods to operate on an Open Street Map file
/// <summary>

// Import relevant files & libraries
#include <iostream>
#include <string>
#include <cassert>
#include "osm.h"
using namespace std;
using namespace tinyxml2;

// Open and load XML document
bool osmLoadMapFile(string filename, XMLDocument& xmldoc)
{
  // load document
  xmldoc.LoadFile(filename.c_str());
  // error handling
  if (xmldoc.ErrorID() != 0) {
    cout << "**ERROR: unable to open XML file '" << filename << "'." << endl;
    return false;
  }

  // check top-level element
  XMLElement* osm = xmldoc.FirstChildElement("osm");
  if (osm == nullptr) {
    cout << "**ERROR: unable to find top-level 'osm' XML element." << endl;
    cout << "**ERROR: this file is probably not an Open Street Map." << endl;
    return false;
  }

  return true;
}

// Parse through all tags associated with XML element and determine if key,value pair exists
bool osmContainsKeyValue(XMLElement* e, string key, string value) {
  XMLElement* tag = e->FirstChildElement("tag");

  while (tag != nullptr) {
    const XMLAttribute* keyAttribute = tag->FindAttribute("k");
    const XMLAttribute* valueAttribute = tag->FindAttribute("v");

    if (keyAttribute != nullptr && valueAttribute != nullptr) {
      string elemkey(keyAttribute->Value());
      string elemvalue(valueAttribute->Value());

      // key,value pair exists
      if (elemkey == key && elemvalue == value) {
        return true;
      }
    }
    tag = tag->NextSiblingElement("tag");
  }
  // key,value pair doesn't exist
  return false;
}

// Find value corresponding to key associated with XMl element
string osmGetKeyValue(XMLElement* e, string key) {
  XMLElement* tag = e->FirstChildElement("tag");

  while (tag != nullptr) {
    const XMLAttribute* keyAttribute = tag->FindAttribute("k");
    const XMLAttribute* valueAttribute = tag->FindAttribute("v");

    if (keyAttribute != nullptr && valueAttribute != nullptr) {
      string elemkey(keyAttribute->Value());
      
      // value found
      if (elemkey == key) {
        string elemvalue(valueAttribute->Value());
        return elemvalue;
      }
    }
    tag = tag->NextSiblingElement("tag");
  }

  // value not found
  return "";
}