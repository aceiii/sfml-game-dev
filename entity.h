#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "scenenode.h"

#include <SFML/System/Vector2.hpp>


class Entity: public SceneNode
{
public:
    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;

private:
    virtual void updateCurrent(sf::Time deltaTime);

private:
    sf::Vector2f _velocity;
};


#endif//__ENTITY_H__
