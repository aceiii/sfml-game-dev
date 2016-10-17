#include <sstream>
#include <cmath>
#include "aircraft.h"
#include "category.h"
#include "datatables.h"
#include "util.h"
#include "easylogging++.h"
#include "projectile.h"

namespace {
    const std::vector<AircraftData> g_table = initializeAircraftData();
}

Aircraft::Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts)
    :Entity(g_table[type].hitpoints),_type(type),_sprite(textures.get(toTextureId(type)))
{
    std::unique_ptr<TextNode> healthDisplay(new TextNode(fonts, ""));
    _healthDisplay = healthDisplay.get();
    attachChild(std::move(healthDisplay));

    _fireCommand.category = Category::SceneAirLayer;
    _fireCommand.action = [this, &textures] (SceneNode& node, sf::Time) {
        createBullets(node, textures);
    };

    _missileCommand.category = Category::SceneAirLayer;
    _missileCommand.action = [this, &textures] (SceneNode& node, sf::Time) {
        createProjectile(node, Projectile::Missile, 0.0f, 0.5f, textures);
    };
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

void Aircraft::fire() {
    LOG(INFO) << "FIRE!";

    _isFiring = true;
}

void Aircraft::launchMissile() {
    LOG(INFO) << "launch!!";

    _isLaunchingMissile = true;

}

void Aircraft::checkProjectileLaunch(sf::Time dt, CommandQueue &commands) {
    if (!isAllied()) {
        fire();
    }

    if (_isFiring && _fireCountdown <= sf::Time::Zero) {
        commands.push(_fireCommand);
        _fireCountdown += sf::seconds(1.0f / (_fireRateLevel + 1));
        _isFiring = false;
    } else if (_fireCountdown > sf::Time::Zero) {
        _fireCountdown -= dt;
    }

    if (_isLaunchingMissile) {
        commands.push(_missileCommand);
        _isLaunchingMissile = false;
    }
}

void Aircraft::createBullets(SceneNode &node, const TextureHolder &textures) const {
    Projectile::Type type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;

    switch (_spreadLevel) {
    case 1:
        createProjectile(node, type, 0.0f, 0.5f, textures);
        break;
    case 2:
        createProjectile(node, type, -0.33f, 0.33f, textures);
        createProjectile(node, type, 0.33f, 0.33f, textures);
        break;
    case 3:
        createProjectile(node, type, -0.5f, 0.33f, textures);
        createProjectile(node, type, 0.0f, 0.5f, textures);
        createProjectile(node, type, 0.5f, 0.33f, textures);
        break;
    }
}

void Aircraft::createProjectile(SceneNode &node, Projectile::Type type, float xOffset, float yOffset,
                                const TextureHolder &textures) const {

    std::unique_ptr<Projectile> projectile(new Projectile(type, textures));

    sf::FloatRect bounds = _sprite.getGlobalBounds();
    sf::Vector2f offset(xOffset * bounds.width, yOffset * bounds.height);
    sf::Vector2f velocity(0, projectile->getMaxSpeed());

    float sign = isAllied() ? -1.0f : 1.0f;
    projectile->setPosition(getWorldPosition() + offset * sign);
    projectile->setVelocity(velocity * sign);

    node.attachChild(std::move(projectile));
}

bool Aircraft::isAllied() const {
    int category = getCategory();
    return category != Category::EnemyAircraft;
}

void Aircraft::collectMissiles(int i) {
    _missileCount += i;
}

void Aircraft::increaseFireSpread() {
    _spreadLevel += 1;
}

void Aircraft::increaseFireRate() {
    _fireRateLevel += 1;
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

