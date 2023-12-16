/*osm.h*/

/// <sumary>
/// Header file for osm.cpp
/// <summary>

// Import relevant files & libraries
#pragma once
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

// Methods provided
bool osmLoadMapFile(string filename, XMLDocument& xmldoc);

bool osmContainsKeyValue(XMLElement* e, string key, string value);

string osmGetKeyValue(XMLElement* e, string key);