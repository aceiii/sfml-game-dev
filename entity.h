#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "scenenode.h"
#include "commandqueue.h"

#include <SFML/System/Vector2.hpp>


class Entity: public SceneNode
{
public:
    explicit Entity(int hitpoints);
    void repair(int points);
    void damage(int points);
    void destroy();

    int getHitpoints() const;
    virtual bool isDestroyed() const override;

    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;

protected:
    virtual void updateCurrent(sf::Time deltaTime, CommandQueue& commands) override ;

private:
    int _hitpoints;
    sf::Vector2f _velocity;
};


#endif//__ENTITY_H__
