//Filter.cpp

#include "Filter.h"
#include "Pantry.h"

bool matchesFilters(const Pantry& p, const FilterConfiguration& f) 
{
    if (f.requireHalal 
     && !p.halal) { return false; }

    if (f.requireKosher 
     && !p.kosher) { return false; }

    if (f.requireVegan 
     && !p.vegan)  { return false; }

    if (f.requireVegetarian
     && !p.vegetarian)  { return false; }

    if (f.requireCarnivore 
     && !p.carnivore)  { return false; }

    if (f.requireHandicapAccessible 
     && !p.handicapAccessible)  { return false; }

    if (f.maxDistance >= 0 
     && p.latitude > f.maxDistance) { return false; } // (wip)

    return true;
}