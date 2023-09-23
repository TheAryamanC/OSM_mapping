/*footways.h*/

#pragma once

#include <vector>

#include "building.h"
#include "footway.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

class Footways
{
public:
    vector<Footway> MapFootways;

    void readMapFootways(XMLDocument& xmldoc);

    int getNumMapFootways();

    void print_get_intersection(Building& B);
};