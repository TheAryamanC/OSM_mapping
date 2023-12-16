/*footways.cpp*/

/// <sumary>
/// This file provides methods to operate over a collection of footways
/// <summary>

// Import relevant files & libraries
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include "footways.h"
#include "osm.h"
#include "tinyxml2.h"


// Parse through document and read footwats
void Footways::readMapFootways(XMLDocument& xmldoc) {
    XMLElement* osm = xmldoc.FirstChildElement("osm");
    assert(osm != nullptr);
    
    // Parse through way by way looking for walkable footways:
    XMLElement* way = osm->FirstChildElement("way");

    while (way != nullptr) {
        const XMLAttribute* attr = way->FindAttribute("id");
        assert(attr != nullptr);

        // Footways
        if (osmContainsKeyValue(way, "highway", "footway") || osmContainsKeyValue(way, "area:highway", "footway")) {
            // Create footway object
            long long id = attr->Int64Value();
            Footway F(id);

            XMLElement* nd = way->FirstChildElement("nd");
            while (nd != nullptr) {
                const XMLAttribute* ndref = nd->FindAttribute("ref");
                assert(ndref != nullptr);
                long long id = ndref->Int64Value();
                F.add(id);
                nd = nd->NextSiblingElement("nd");
            }
            // Store footway in vector
            this->MapFootways.push_back(F);
        }
        way = way->NextSiblingElement("way");
    }
}

// Access data - number of footways
int Footways::getNumMapFootways() {
    return (int) this->MapFootways.size();
}

// Access data - find all footways that intersect with a specified building
void Footways::print_get_intersection(Building& B) {
    vector<long long> footway_ids;
    for (Footway f : this->MapFootways) {
        if (f.check_node(B)) {
            footway_ids.push_back(f.ID);
        }
    }
    
    // return footways sorted by ID (or none)
    if (footway_ids.size() == 0) {
        cout << "  None" << endl;
        return;
    }
    else {
        sort(footway_ids.begin(), footway_ids.end(),
            [](long long id1, long long id2)
            {
                if (id1 < id2) {
                    return true;
                }
                else {
                    return false;
                }
            }
        );
        for (long long id : footway_ids) {
            cout << "  Footway " << id << endl;
        }
        return;
    }
}