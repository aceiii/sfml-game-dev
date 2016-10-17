#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#include "entity.h"
#include "textureholder.h"
#include "textnode.h"
#include "commandqueue.h"
#include "projectile.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>


class Aircraft: public Entity
{
public:
    enum Type {
        Eagle,
        Raptor,
        Avenger,
        TypeCount,
    };

public:
    explicit Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts);

    virtual unsigned int getCategory() const override;

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

    void accelerate(sf::Vector2f velocity);
    void accelerate(float vx, float vy);

    bool isAllied() const;
    void fire();
    void launchMissile();

    void collectMissiles(int i);
    void increaseFireSpread();
    void increaseFireRate();

    virtual sf::FloatRect getBoundingRect() const override;

private:
    virtual void updateCurrent(sf::Time delta) override;

    void updateMovementPattern(sf::Time dt);

    float getMaxSpeed() const;

    void checkProjectileLaunch(sf::Time dt, CommandQueue& commands);
    void createBullets(SceneNode& node, const TextureHolder& textures) const;
    void createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const;

private:
    Type _type;
    sf::Sprite _sprite;
    TextNode* _healthDisplay;
    float _travelledDistance;
    int _directionIndex;
    bool _isFiring;
    bool _isLaunchingMissile;
    int _fireRateLevel;
    int _spreadLevel;
    int _missileCount;
    sf::Time _fireCountdown;
    Command _fireCommand;
    Command _missileCommand;
};


Textures::ID toTextureId(Aircraft::Type type);


#endif//__AIRCRAT_H__
