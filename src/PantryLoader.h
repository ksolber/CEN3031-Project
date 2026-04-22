#pragma once
#include <string>
#include <vector>

#include "Pantry.h"

using namespace std;

vector<Pantry> loadPantriesFromLocationFile(const string &filename);

vector<Pantry> loadPantriesFromLocationFile(const string &filename, double userLat,
                                            double userLong);
