#include "spritenode.h"


SpriteNode::SpriteNode(const sf::Texture& texture):
    SceneNode(),
    _sprite(texture)
{
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& rect):
    SceneNode(),
    _sprite(texture, rect)
{
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}
