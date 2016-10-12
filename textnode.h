#ifndef __TEXT_NODE_H__
#define __TEXT_NODE_H__

#include "scenenode.h"
#include "fontholder.h"


class TextNode: public SceneNode {
public:
    explicit TextNode(const FontHolder& fonts, const std::string& text);

    void setString(const std::string& text);

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Text _text;
};


#endif//__TEXT_NODE_H__
