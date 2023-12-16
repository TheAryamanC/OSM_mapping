/*dist.cpp*/

/// <sumary>
/// This file provides a methods to find the distance (in miles) between two sets of coordinates
/// <summary> 

// Import relevant files & libraries
#include <iostream>
#include <cmath>
#include "dist.h"
using namespace std;


// Find distance between two pairs of coordinates
// NOTE: the pair of coordinates used first could have an impact on the result
double distBetween2Points(double lat1, double long1, double lat2, double long2) {
  // We can use the haversine distance formula to do this
  double PI = 3.14159265;
  double earth_rad = 3963.1;

  double lat1_rad = lat1 * PI / 180.0;
  double long1_rad = long1 * PI / 180.0;
  double lat2_rad = lat2 * PI / 180.0;
  double long2_rad = long2 * PI / 180.0;

  double dist = earth_rad * acos(
    (cos(lat1_rad) * cos(long1_rad) * cos(lat2_rad) * cos(long2_rad))
    +
    (cos(lat1_rad) * sin(long1_rad) * cos(lat2_rad) * sin(long2_rad))
    +
    (sin(lat1_rad) * sin(lat2_rad))
  );

  return dist;
}
