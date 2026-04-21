#include "Pantry.h"

#include <cmath>

// Implements the function to get pantry status.
// Returns "Available" if the pantry is open, otherwise "Unavailable".
std::string getPantryStatus(bool isOpen) {
  if (isOpen) {
    return "Available";
  } else {
    return "Unavailable";
  }
}

// Calculates the distance in miles between two coordinates using the Haversine formula.
double calcDistance(double lat1, double lon1, double lat2, double lon2) {
  const double earthRadiusMiles = 3958.8;
  const double toRad = M_PI / 180.0;

  double dLat = (lat2 - lat1) * toRad;
  double dLon = (lon2 - lon1) * toRad;

  double a = sin(dLat / 2) * sin(dLat / 2) +
             cos(lat1 * toRad) * cos(lat2 * toRad) * sin(dLon / 2) * sin(dLon / 2);

  double c = 2 * atan2(sqrt(a), sqrt(1 - a));

  return earthRadiusMiles * c;
}

// WIP - Add constructor/destructor
