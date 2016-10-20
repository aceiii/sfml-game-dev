#include "entity.h"

Entity::Entity(int hitpoints):_hitpoints(hitpoints) {
}

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

void Entity::updateCurrent(sf::Time dt, CommandQueue& commands) {
    move(_velocity * dt.asSeconds());
}

void Entity::repair(int points) {
    _hitpoints += points;
}

void Entity::damage(int points) {
    _hitpoints -= points;
}

void Entity::destroy() {
    _hitpoints = 0;
}

int Entity::getHitpoints() const {
    return _hitpoints;
}

bool Entity::isDestroyed() const {
    return _hitpoints <= 0;
}

void Entity::accelerate(sf::Vector2f velocity) {
    _velocity += velocity;
}

void Entity::accelerate(float vx, float vy) {
    _velocity.x += vx;
    _velocity.y += vy;
}
