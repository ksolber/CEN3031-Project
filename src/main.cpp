#include <iostream>
#include <vector>

#include "Filter.h"
#include "Pantry.h"
#include "PantryLoader.h"

using namespace std;

int main() {
  vector<Pantry> pantries = loadPantriesFromLocationFile("data/locations.txt");

  if (pantries.empty()) {
    cout << "Unable to load pantry data." << endl;
    return 1;
  }

  // TODO: Replace with actual user location from UI later
  const double userLat = 29.6516;
  const double userLon = -82.3248;

  for (Pantry &pantry : pantries) {
    pantry.distanceFromUser = calcDistance(userLat, userLon, pantry.latitude, pantry.longitude);
  }

  FilterOptions filters;
  filters.requireVegetarian = true;
  filters.maxDistance = 5.0;

  vector<Pantry> results = filterPantries(pantries, filters);

  cout << "Loaded " << pantries.size() << " pantry locations.\n";
  cout << "Vegetarian matches: " << results.size() << "\n\n";

  // For printing results via terminal
  for (const Pantry &p : results) {
    cout << "Name: " << p.name << '\n';
    cout << "Address: " << p.address << '\n';
    cout << "Hours: " << p.hours << '\n';
    cout << "Vegan: " << (p.vegan ? "Yes" : "No") << '\n';
    cout << "Vegetarian: " << (p.vegetarian ? "Yes" : "No") << '\n';
    cout << "Halal: " << (p.halal ? "Yes" : "No") << '\n';
    cout << "Kosher: " << (p.kosher ? "Yes" : "No") << '\n';
    cout << "Carnivore: " << (p.carnivore ? "Yes" : "No") << '\n';
    cout << "Accessible: " << (p.handicapAccessible ? "Yes" : "No") << '\n';
    cout << "Distance: " << p.distanceFromUser << " miles\n";
    cout << "----------------------------------\n";
  }

  return 0;
}
