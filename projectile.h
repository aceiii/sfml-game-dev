#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "textureholder.h"
#include "commandqueue.h"
#include "entity.h"


class Projectile: public Entity {
public:
    enum Type {
        AlliedBullet,
        EnemyBullet,
        Missile,
        TypeCount,
    };

public:
    Projectile(Type type, const TextureHolder& textures);

    void guideTowards(sf::Vector2f position);
    bool isGuided() const;

    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;
    float getMaxSpeed() const;
    int getDamage() const;

private:
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Type _type;
    sf::Sprite _sprite;
    sf::Vector2f _targetDirection;
};


#endif//__PROJECTILE_H__
