#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Filter.h"
#include "Pantry.h"

using namespace std;

Pantry makePantry(const string& name, double distanceFromUser = 0.0, bool halal = false,
                  bool kosher = false, bool vegan = false, bool vegetarian = false,
                  bool carnivore = false, bool handicapAccessible = false) {
  Pantry pantry;
  pantry.name = name;
  pantry.distanceFromUser = distanceFromUser;
  pantry.halal = halal;
  pantry.kosher = kosher;
  pantry.vegan = vegan;
  pantry.vegetarian = vegetarian;
  pantry.carnivore = carnivore;
  pantry.handicapAccessible = handicapAccessible;

  return pantry;
}

// TEST-03 - Verify that the system displays only pantries with handicap-accessible entry when the
// accessibility filter is selected.
void testHandicapAccessibleFilter() {
  vector<Pantry> pantries;
  pantries.push_back(makePantry("Pantry A", false, false, false, false, false, true));
  pantries.push_back(makePantry("Pantry B", false, false, false, false, false, false));
  pantries.push_back(makePantry("Pantry C", false, false, false, false, false, true));

  FilterOptions filters;
  filters.requireHandicapAccessible = true;

  vector<Pantry> results = filterPantries(pantries, filters);

  assert(results.size() == 2);
  assert(results[0].name == "Pantry A");
  assert(results[1].name == "Pantry C");

  cout << "TEST-03 Passed: Handicap-accessible entry filter successful." << endl;
}

// TEST-04 - Verify that the system displays only pantries with vegan options when the vegan filter
// is selected.
void testVeganFilter() {
  vector<Pantry> pantries;
  pantries.push_back(makePantry("Pantry A", false, false, true, false, false, false));
  pantries.push_back(makePantry("Pantry B", false, false, false, false, false, false));
  pantries.push_back(makePantry("Pantry C", false, false, true, false, false, false));

  FilterOptions filters;
  filters.requireVegan = true;

  vector<Pantry> results = filterPantries(pantries, filters);

  assert(results.size() == 2);
  assert(results[0].name == "Pantry A");
  assert(results[1].name == "Pantry C");

  cout << "TEST-04 Passed: Vegan filter successful." << endl;
}

// TEST-05 - Verify that the system correctly applies multiple filters at the same time.
void testMultipleFilters() {
  vector<Pantry> pantries;

  pantries.push_back(makePantry("Pantry A", false, false, false, true, false, true));
  pantries.push_back(makePantry("Pantry B", false, false, false, true, false, false));
  pantries.push_back(makePantry("Pantry C", false, false, false, false, false, true));

  FilterOptions filters;
  filters.requireVegetarian = true;
  filters.requireHandicapAccessible = true;

  vector<Pantry> results = filterPantries(pantries, filters);

  assert(results.size() == 1);
  assert(results[0].name == "Pantry A");

  cout << "TEST-05 Passed: Multiple filters work together." << endl;
}

// TEST-06 - Verify that the system displays only pantries with kosher options when the kosher
// filter is selected.
void testKosherFilter() {
  vector<Pantry> pantries;

  pantries.push_back(makePantry("Pantry A", false, true, false, false, false, false));
  pantries.push_back(makePantry("Pantry B", false, false, false, false, false, false));
  pantries.push_back(makePantry("Pantry C", false, true, false, false, false, false));

  FilterOptions filters;
  filters.requireKosher = true;

  vector<Pantry> results = filterPantries(pantries, filters);

  assert(results.size() == 2);
  assert(results[0].name == "Pantry A");
  assert(results[1].name == "Pantry C");

  cout << "TEST-06 Passed: Kosher filter successful." << endl;
}

// TEST-07 - Verify that the system returns no pantries when no pantry matches the selected filters.
void testNoMatchingResults() {
  vector<Pantry> pantries;

  pantries.push_back(makePantry("Pantry A", false, false, false, true, false, false));
  pantries.push_back(makePantry("Pantry B", false, false, true, false, false, false));

  FilterOptions filters;
  filters.requireHalal = true;
  filters.requireHandicapAccessible = true;

  vector<Pantry> results = filterPantries(pantries, filters);

  assert(results.empty());

  cout << "TEST-07 Passed: No-match filter case successful." << endl;
}

//----------------DISTANCE-TESTS-------------------------//

// TEST-08 - Verify that the system displays only pantries within the selected max distance.
void testDistanceFilterOnly() {
  vector<Pantry> pantries;
  pantries.push_back(makePantry("Pantry A", 1.2));
  pantries.push_back(makePantry("Pantry B", 3.8));
  pantries.push_back(makePantry("Pantry C", 6.1));

  FilterOptions filters;
  filters.maxDistance = 5.0;

  vector<Pantry> results = filterPantries(pantries, filters);

  assert(results.size() == 2);
  assert(results[0].name == "Pantry A");
  assert(results[1].name == "Pantry B");

  cout << "TEST-01 Passed: Distance-only filter successful." << endl;
}

// TEST-02 - Verify that a pantry beyond the max distance is excluded.

void testDistanceFilterExcludesFarPantries() {
  vector<Pantry> pantries;
  pantries.push_back(makePantry("Nearby Pantry", 2.0));
  pantries.push_back(makePantry("Far Pantry", 10.0));

  FilterOptions filters;
  filters.maxDistance = 5.0;

  vector<Pantry> results = filterPantries(pantries, filters);

  assert(results.size() == 1);
  assert(results[0].name == "Nearby Pantry");

  cout << "TEST-02 Passed: Far pantries are excluded from filters successfully." << endl;
}

// TEST-03 - Verify that the system correctly applies distance and vegetarian filters together.
void testDistanceAndVegetarianFilter() {
  vector<Pantry> pantries;
  pantries.push_back(makePantry("Pantry A", 2.5, false, false, false, true));
  pantries.push_back(makePantry("Pantry B", 6.0, false, false, false, true));
  pantries.push_back(makePantry("Pantry C", 3.0, false, false, false, false));

  FilterOptions filters;
  filters.maxDistance = 5.0;
  filters.requireVegetarian = true;

  vector<Pantry> results = filterPantries(pantries, filters);

  assert(results.size() == 1);
  assert(results[0].name == "Pantry A");

  cout << "TEST-03 Passed: Distance + vegetarian filter successful." << endl;
}

// TEST-04 - Verify that the system correctly applies distance and accessibility filters together.
void testDistanceAndAccessibilityFilter() {
  vector<Pantry> pantries;
  pantries.push_back(makePantry("Pantry A", 1.0, false, false, false, false, false, true));
  pantries.push_back(makePantry("Pantry B", 2.0, false, false, false, false, false, false));
  pantries.push_back(makePantry("Pantry C", 7.0, false, false, false, false, false, true));

  FilterOptions filters;
  filters.maxDistance = 5.0;
  filters.requireHandicapAccessible = true;

  vector<Pantry> results = filterPantries(pantries, filters);

  assert(results.size() == 1);
  assert(results[0].name == "Pantry A");

  cout << "TEST-04 Passed: Distance + accessibility filter successful." << endl;
}

// TEST-05 - Verify that no pantries are returned if none meet the distance requirement.
void testDistanceFilterNoMatches() {
  vector<Pantry> pantries;
  pantries.push_back(makePantry("Pantry A", 8.0));
  pantries.push_back(makePantry("Pantry B", 9.5));

  FilterOptions filters;
  filters.maxDistance = 5.0;

  vector<Pantry> results = filterPantries(pantries, filters);

  assert(results.empty());

  cout << "TEST-05 Passed: No matches case for distance filter successful." << endl;
}

int main() {
  testHandicapAccessibleFilter();
  testVeganFilter();
  testMultipleFilters();
  testKosherFilter();
  testNoMatchingResults();

  // Distance
  testDistanceFilterOnly();
  testDistanceFilterExcludesFarPantries();
  testDistanceAndVegetarianFilter();
  testDistanceAndAccessibilityFilter();
  testDistanceFilterNoMatches();

  cout << "All filter tests successfully passed" << endl;
  return 0;
}
