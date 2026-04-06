#pragma once
#include "Pantry.h"
#include <string>
#include <vector>

using namespace std;

vector<Pantry> loadPantriesFromLocationFile(const string &filename);
