#include <sstream>
#include <cmath>
#include "aircraft.h"
#include "category.h"
#include "datatables.h"
#include "util.h"

namespace {
    const std::vector<AircraftData> g_table = initializeAircraftData();
}

Aircraft::Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts)
    :Entity(g_table[type].hitpoints),_type(type),_sprite(textures.get(toTextureId(type)))
{
    std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
    _healthDisplay = healthDisplay.get();
    attachChild(std::move(healthDisplay));
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}

unsigned int Aircraft::getCategory() const {
    switch (_type) {
    case Eagle:
        return Category::PlayerAircraft;
    default:
        return Category::EnemyAircraft;
    }
}

void Aircraft::accelerate(sf::Vector2f velocity) {
    setVelocity(getVelocity() + velocity);
}

void Aircraft::accelerate(float vx, float vy) {
    setVelocity(vx, vy);
}

void Aircraft::updateCurrent(sf::Time delta) {
    _healthDisplay->setString(toString(getHitpoints()) + " HP");
    _healthDisplay->setPosition(0.0f, 50.0f);
    _healthDisplay->setRotation(-getRotation());
}

void Aircraft::updateMovementPattern(sf::Time dt) {
    const std::vector<Direction>& directions = g_table[_type].directions;
    if (!directions.empty()) {
        float distanceToTravel = directions[_directionIndex].distance;
        if (_travelledDistance > distanceToTravel) {
            _directionIndex = (_directionIndex + 1) % directions.size();
            _travelledDistance = 0.0f;
        }

        float radians = toRadians(directions[_directionIndex].angle + 90.0f);
        float vx = getMaxSpeed() * std::cos(radians);
        float vy = getMaxSpeed() * std::sin(radians);

        setVelocity(vx, vy);

        _travelledDistance += getMaxSpeed() * dt.asSeconds();
    }
}

float Aircraft::getMaxSpeed() const {
    sf::Vector2f velocity = getVelocity();
    return sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
}

Textures::ID toTextureId(Aircraft::Type type) {
    switch (type) {
    case Aircraft::Eagle:
        return Textures::Eagle;
    case Aircraft::Raptor:
        return Textures::Raptor;
    default:
        assert(false);
        return Textures::Eagle;
    }
}

