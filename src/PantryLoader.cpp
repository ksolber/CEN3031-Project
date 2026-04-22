#include "PantryLoader.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

using namespace std;

namespace {
string readEntireFile(const string &filename) {
  ifstream inFile(filename);
  if (!inFile.is_open()) {
    return "";
  }

  ostringstream buffer;
  buffer << inFile.rdbuf();
  return buffer.str();
}

string extractStringValue(const string &block, const string &key) {
  regex pattern("\"" + key + "\"\\s*:\\s*(None|\"([^\"]*)\")");
  smatch match;

  if (regex_search(block, match, pattern)) {
    if (match[1] == "None") {
      return "";
    }

    if (match.size() >= 3) {
      return match[2].str();
    }
  }

  return "";
}

double extractDoubleValue(const string &block, const string &key) {
  regex pattern("\"" + key + "\"\\s*:\\s*(-?\\d+(?:\\.\\d+)?)");
  smatch match;

  if (regex_search(block, match, pattern)) {
    return stod(match[1].str());
  }

  return 0.0;
}

bool extractBoolValue(const string &block, const string &key) {
  regex pattern("\"" + key + "\"\\s*:\\s*(true|false)");
  smatch match;

  if (regex_search(block, match, pattern)) {
    return match[1].str() == "true";
  }

  return false;
}

string extractDescription(const string &block) {
  regex pattern("\"description\"\\s*:\\s*\\(([\\s\\S]*?)\\)\\s*,");
  smatch match;

  if (!regex_search(block, match, pattern)) {
    return "";
  }

  string descriptionBlock = match[1].str();
  regex stringPattern("\"([^\"]*)\"");
  sregex_iterator begin(descriptionBlock.begin(), descriptionBlock.end(), stringPattern);
  sregex_iterator end;

  string description;
  for (sregex_iterator it = begin; it != end; ++it) {
    description += (*it)[1].str();
  }

  return description;
}

vector<string> splitIntoObjectBlocks(const string &fileContents) {
  vector<string> blocks;
  bool insideObject = false;
  int braceDepth = 0;
  string current;

  for (char ch : fileContents) {
    if (ch == '{') {
      if (!insideObject) {
        insideObject = true;
        current.clear();
      }

      braceDepth++;
    }

    if (insideObject) {
      current += ch;
    }

    if (ch == '}') {
      braceDepth--;

      if (insideObject && braceDepth == 0) {
        blocks.push_back(current);
        current.clear();
        insideObject = false;
      }
    }
  }

  return blocks;
}

Pantry parsePantryBlock(const string &block) {
  Pantry pantry;

  pantry.name = extractStringValue(block, "name");
  pantry.address = extractStringValue(block, "address");
  pantry.latitude = extractDoubleValue(block, "latitude");
  pantry.longitude = extractDoubleValue(block, "longitude");
  pantry.description = extractDescription(block);
  pantry.hours = extractStringValue(block, "hours");
  pantry.eligibility = extractStringValue(block, "eligibility");
  pantry.phone = extractStringValue(block, "phone");
  pantry.email = extractStringValue(block, "email");
  pantry.website = extractStringValue(block, "website");
  pantry.notes = pantry.description;

  pantry.halal = extractBoolValue(block, "halal");
  pantry.kosher = extractBoolValue(block, "kosher");
  pantry.vegan = extractBoolValue(block, "vegan");
  pantry.vegetarian = extractBoolValue(block, "vegetarian");
  pantry.carnivore = extractBoolValue(block, "carnivore");
  pantry.servesAllergens = extractBoolValue(block, "servesAllergens");
  pantry.handicapAccessible = extractBoolValue(block, "handicapAccessible");

  return pantry;
}
}  // namespace

vector<Pantry> loadPantriesFromLocationFile(const string &filename) {
  vector<Pantry> pantries;
  string fileContents = readEntireFile(filename);

  if (fileContents.empty()) {
    cerr << "Error: Could not open or read file: " << filename << '\n';
    return pantries;
  }

  vector<string> blocks = splitIntoObjectBlocks(fileContents);

  for (const string &block : blocks) {
    Pantry pantry = parsePantryBlock(block);

    if (!pantry.name.empty()) {
      pantries.push_back(pantry);
    }
  }

  return pantries;
}

vector<Pantry> loadPantriesFromLocationFile(const string &filename, double userLat,
                                            double userLong) {
  vector<Pantry> pantries = loadPantriesFromLocationFile(filename);

  for (Pantry &pantry : pantries) {
    pantry.distanceFromUser = calcDistance(userLat, userLong, pantry.latitude, pantry.longitude);
  }

  return pantries;
}
