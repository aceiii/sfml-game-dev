#include <sstream>
#include "aircraft.h"
#include "category.h"
#include "datatables.h"

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

std::string Aircraft::toString(int i) const {
    std::stringstream ss;
    ss << i;
    return ss.str();
}

Textures::ID toTextureId(Aircraft::Type type) {
    switch (type) {
    case Aircraft::Eagle:
        return Textures::Eagle;
    case Aircraft::Raptor:
        return Textures::Raptor;
    }
}

