#include "pantry.h"
#include <cassert>
#include <iostream>
#include <string>

// TEST-01
// Verify that a user can successfully view the current availability status of
// food pantries on teh Home screen list.
void testPantryIsAvailable() {
  // Arrange
  bool isOpen = true;
  std::string expected = "Available";

  // Action
  std::string actual = getPantryStatus(isOpen);

  // Assert
  assert(actual == expected);

  std::cout << "TEST-01 Passed: Pantry is Available." << std::endl;
}

// TEST-02
// Verify that a user can clearly see when a food pantry is currently
// unavailable on the home screen list.
void testPantryIsUnavailable() {
  // Arrange
  bool isOpen = false;
  std::string expected = "Unavailable";

  // Action
  std::string actual = getPantryStatus(isOpen);

  // Assert
  assert(actual == expected);

  std::cout << "TEST-02 Passed: Pantry is Unavailable." << std::endl;
}

int testMain() {
  testPantryIsAvailable();
  testPantryIsUnavailable();
  return 0;
}
