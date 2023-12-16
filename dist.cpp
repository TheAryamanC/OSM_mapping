/*dist.cpp*/

/// <sumary>
/// This file provides a method to find the distance (in miles) between two sets of coordinates
/// <summary>

// Import relevant files & libraries
#include <iostream>
#include <cmath>
#include "dist.h"
using namespace std;

// Find distance between two pairs of coordinates
// NOTE: the order of the pairs of coordinates could have an impact on the result
double distBetween2Points(double lat1, double long1, double lat2, double long2) {
  // We can use the haversine distance formula to do this
  // Reference: https://en.wikipedia.org/wiki/Haversine_formula
  double earth_rad = 3963.1;

  double diff_lat = (lat1 - lat2) / 2;
  double diff_long = (long1 - long2) / 2;

  double dist = 2 * earth_rad * asin(sqrt((sin(diff_lat) * sin(diff_lat)) + (cos(lat1) * cos(lat2) * sin(diff_long) * sin(diff_long))));

  return dist;
}