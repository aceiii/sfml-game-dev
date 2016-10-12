#include "aircraft.h"
#include "category.h"
#include "datatables.h"

namespace {
    const std::vector<AircraftData> g_table = initializeAircraftData();
}

Aircraft::Aircraft(Type type, const TextureHolder& textures)
    :Entity(g_table[type].hitpoints),_type(type),_sprite(textures.get(toTextureId(type)))
{
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

Textures::ID toTextureId(Aircraft::Type type) {
    switch (type) {
    case Aircraft::Eagle:
        return Textures::Eagle;
    case Aircraft::Raptor:
        return Textures::Raptor;
    }
}

