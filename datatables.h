#ifndef __DATA_TABLES_H__
#define __DATA_TABLES_H__

#include <vector>
#include "textures.h"
#include "aircraft.h"


struct Direction {
    Direction(float angle, float distance);

    float angle;
    float distance;
};

struct AircraftData {
    int hitpoints;
    float speed;
    Textures::ID texture;
    std::vector<Direction> directions;
};

struct ProjectileData {
    Textures::ID texture;
    int damage;
    float speed;
};

struct PickupData {
    Textures::ID texture;
    std::function<void(Aircraft&)> action;
};

std::vector<AircraftData> initializeAircraftData();
std::vector<ProjectileData> initializeProjectileData();
std::vector<PickupData> initializePickupData();


#endif//__DATA_TABLES_H__
