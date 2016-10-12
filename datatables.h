#ifndef __DATA_TABLES_H__
#define __DATA_TABLES_H__

#include <vector>
#include "textures.h"
#include "aircraft.h"


struct AircraftData {
    int hitpoints;
    float speed;
    Textures::ID texture;
};


std::vector<AircraftData> initializeAircraftData();


#endif//__DATA_TABLES_H__
