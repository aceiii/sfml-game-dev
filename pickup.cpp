#include "pickup.h"
#include "datatables.h"

namespace {
    std::vector<PickupData> g_table = initializePickupData();
}

Pickup::Pickup(Pickup::Type type, const TextureHolder &textures):
    Entity(0)
{
}

unsigned int Pickup::getCategory() const {
    return SceneNode::getCategory();
}

sf::FloatRect Pickup::getBoundingRect() const {
    return sf::FloatRect();
}

void Pickup::apply(Aircraft &player) const {
    g_table[_type].action(player);
}

void Pickup::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}
