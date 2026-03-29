//Filter.h

#pragma once

struct FilterConfiguration
{
    //Initialize all params as false at start
    bool requireHalal = false;
    bool requireKosher = false;
    bool requireVegan = false;
    bool requireVegetarian = false;
    bool requireCarnivore = false;
    bool requireHandicapAccessible = false;

    double maxDistance = -1.0;
};