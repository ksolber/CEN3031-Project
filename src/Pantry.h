//Pantry.h

using namespace std:

struct Pantry 
{
    string name;
    string address;

    //Coordinates (if we can gather it)
    double latitude;
    double longitude;

    
    double distanceFromCampus;
    double distanceFromUser;

    //diets
    bool halal;
    bool kosher;
    bool vegan;
    bool vegetarian;
    bool carnivore;
    bool handicapAccessible;
    
    //wip
    bool appointmentRequired;
    bool studentOnly;

    //hours info
    string hours;
    string notes;
};