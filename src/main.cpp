#include <vector>
#include <iostream>
#include "Pantry.h"
#include "Filter.h"

using namespace std:

int main() 
{
    vector<Pantry> pantries;

    // load data from file/repository

    FilterOptions filters;
    filters.requireVegan = true;

    for (const Pantry& p : pantries)
    {
        if (matchesFilters(p, filters))	{ cout << p.name << endl;  }
    }

    return 0;
}