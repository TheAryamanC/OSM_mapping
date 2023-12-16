/*footways.h*/

/// <sumary>
/// Header file for footways.cpp
/// <summary>

// Import relevnt files & libraries
#pragma once
#include <vector>
#include "building.h"
#include "footway.h"
#include "tinyxml2.h"
using namespace std;
using namespace tinyxml2;

// Collection of footway objects
class Footways
{
public:
    vector<Footway> MapFootways;

    void readMapFootways(XMLDocument& xmldoc);

    int getNumMapFootways();

    void print_get_intersection(Building& B);
};