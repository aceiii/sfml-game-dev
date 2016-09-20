#include "entity.h"

void Entity::setVelocity(sf::Vector2f velocity) {
    _velocity = velocity;
}

void Entity::setVelocity(float vx, float vy) {
    _velocity.x = vx;
    _velocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const {
    return _velocity;
}

void Entity::updateCurrent(sf::Time dt) {
    move(_velocity * dt.asSeconds());
}

