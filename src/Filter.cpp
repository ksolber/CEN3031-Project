#include "Filter.h"

#include "Pantry.h"

using namespace std;

bool matchesFilters(const Pantry &p, const FilterOptions &f) {
  if (f.requireHalal && !p.halal) {
    return false;
  }

  if (f.requireKosher && p.kosher == false) {
    return false;
  }

  if (f.requireVegan && p.vegan == false) {
    return false;
  }

  if (f.requireVegetarian && p.vegetarian == false) {
    return false;
  }

  if (f.requireCarnivore && p.carnivore == false) {
    return false;
  }

  if (f.requireHandicapAccessible && p.handicapAccessible == false) {
    return false;
  }

  // if (f.maxDistance >= 0.0
  //&& p.latitude > f.maxDistance) { return false; } // (wip)

  return true;
}

vector<Pantry> filterPantries(const vector<Pantry> &pantries, const FilterOptions &f) {
  vector<Pantry> results;

  for (const Pantry &pantry : pantries) {
    if (matchesFilters(pantry, f)) {
      results.push_back(pantry);
    }
  }

  return results;
}