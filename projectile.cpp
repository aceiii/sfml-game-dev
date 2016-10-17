#include <cmath>
#include "projectile.h"
#include "datatables.h"
#include "util.h"

namespace {
    std::vector<ProjectileData> g_table = initializeProjectileData();
}

Projectile::Projectile(Projectile::Type type, const TextureHolder &textures):
    Entity(1),_type(type),_sprite(textures.get(g_table[type].texture)) {
    centerOrigin(_sprite);
}

void Projectile::guideTowards(sf::Vector2f position) {
    assert(isGuided());
    _targetDirection = unitVector(position - getWorldPosition());
}

bool Projectile::isGuided() const {
    return _type == Missile;
}

unsigned int Projectile::getCategory() const {
    return 0;
}

sf::FloatRect Projectile::getBoundingRect() const {
    return getWorldTransform().transformRect(_sprite.getGlobalBounds());
}

float Projectile::getMaxSpeed() const {
    return 0;
}

int Projectile::getDamage() const {
    return 0;
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue &commands) {
    if (isGuided()) {
        const float approachRate = 200.0f;

        sf::Vector2f newVelocity = unitVector(approachRate * dt.asSeconds() * _targetDirection + getVelocity());
        float angle = std::atan2(newVelocity.y, newVelocity.x);

        setRotation(toDegrees(angle) + 90.0f);
        setVelocity(newVelocity);
    }

    Entity::updateCurrent(dt, commands);
}

void Projectile::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {

}
