#pragma once
#include <vector>

#include "Pantry.h"

using namespace std;

struct FilterOptions {
  // Initialize all params as false at start
  bool requireHalal = false;
  bool requireKosher = false;
  bool requireVegan = false;
  bool requireVegetarian = false;
  bool requireCarnivore = false;
  bool requireHandicapAccessible = false;
  bool excludeAllergenMenus = false;

  double maxDistance = -1.0;
};

bool matchesFilters(const Pantry &p, const FilterOptions &f);
vector<Pantry> filterPantries(const vector<Pantry> &pantries, const FilterOptions &f);
