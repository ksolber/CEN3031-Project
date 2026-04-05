#include "pantry.h"

// Implements the function to get pantry status.
// Returns "Available" if the pantry is open, otherwise "Unavailable".
std::string getPantryStatus(bool isOpen) {
  if (isOpen) {
    return "Available";
  } else {
    return "Unavailable";
  }
}