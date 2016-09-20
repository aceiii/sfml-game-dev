#include "aircraft.h"
#include "category.h"

Aircraft::Aircraft(Type type, const TextureHolder& textures)
    :_type(type),_sprite(textures.get(toTextureId(type)))
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

Textures::ID toTextureId(Aircraft::Type type) {
    switch (type) {
    case Aircraft::Type::Eagle:
        return Textures::ID::Eagle;
    case Aircraft::Type::Raptor:
        return Textures::ID::Raptor;
    }
}

