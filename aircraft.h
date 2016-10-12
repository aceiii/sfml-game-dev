#ifndef __AIRCRAFT_H__
#define __AIRCRAFT_H__

#include "entity.h"
#include "textureholder.h"
#include "textnode.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Sprite.hpp>


class Aircraft: public Entity
{
public:
    enum Type {
        Eagle,
        Raptor,
        TypeCount,
    };

public:
    explicit Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts);

    virtual unsigned int getCategory() const;

    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    void accelerate(sf::Vector2f velocity);
    void accelerate(float vx, float vy);

private:
    virtual void updateCurrent(sf::Time delta) override;

    std::string toString(int i) const;

private:
    Type _type;

    sf::Sprite _sprite;

    TextNode* _healthDisplay;
};


Textures::ID toTextureId(Aircraft::Type type);


#endif//__AIRCRAT_H__
