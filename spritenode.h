#ifndef __SPRITE_NODE_H__
#define __SPRITE_NODE_H__

#include "scenenode.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


class SpriteNode: public SceneNode
{
public:
    explicit SpriteNode(const sf::Texture& texture);
    explicit SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite _sprite;
};


#endif//__SPRITE_NODE_H__
