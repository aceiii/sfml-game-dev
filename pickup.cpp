#include "pickup.h"
#include "datatables.h"
#include "util.h"

namespace {
    std::vector<PickupData> g_table = initializePickupData();
}

Pickup::Pickup(Pickup::Type type, const TextureHolder &textures):
    Entity(0),
    _type(type),
    _sprite(textures.get(g_table[type].texture))
{
    centerOrigin(_sprite);
}

unsigned int Pickup::getCategory() const {
    return Category::Pickup;
}

sf::FloatRect Pickup::getBoundingRect() const {
    return getWorldTransform().transformRect(_sprite.getGlobalBounds());
}

void Pickup::apply(Aircraft &player) const {
    g_table[_type].action(player);
}

void Pickup::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}
