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

  FilterOptions filters;
  filters.requireVegetarian = true;

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
    cout << "----------------------------------\n";
  }

  return 0;
}
