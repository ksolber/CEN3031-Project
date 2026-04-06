#pragma once
#include <string>

using namespace std;

struct Pantry {
  string name;
  string address;

  // Coordinates
  double latitude;
  double longitude;

  double distanceFromCampus;
  double distanceFromUser;

  // diets
  bool halal;
  bool kosher;
  bool vegan;
  bool vegetarian;
  bool carnivore;
  bool handicapAccessible;

  // wip
  bool appointmentRequired;
  bool studentOnly;

  // hours info
  string hours;
  string description;
  string eligibility;
  string phone;
  string email;
  string website;
  string notes;
};

string getPantryStatus(bool isOpen);