#ifndef __AIRCRAFT_MOVER_H__
#define __AIRCRAFT_MOVER_H__

#include <SFML/System/Time.hpp>

#include "aircraft.h"


class SceneNode;

struct AircraftMover
{
    AircraftMover(float vx, float vy):velocity(vx, vy) {}

    void operator() (Aircraft& aircraft, sf::Time) const {
        aircraft.accelerate(velocity);
    }

    sf::Vector2f velocity;
};


#endif//__AIRCRAFT_MOVER_H__
