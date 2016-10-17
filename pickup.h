#ifndef __PICKUP_H__
#define __PICKUP_H__

#include "entity.h"
#include "textureholder.h"
#include "aircraft.h"


class Pickup: public Entity {
public:
    enum Type {
        HealthRefill,
        MissileRefill,
        FireSpread,
        FireRate,
        TypeCount,
    };

public:
    Pickup(Type type, const TextureHolder& textures);

    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;

    void apply(Aircraft& player) const;

protected:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    Type _type;
    sf::Sprite _sprite;
};


#endif//__PICKUP_H__
