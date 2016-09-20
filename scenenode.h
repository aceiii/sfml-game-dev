#ifndef __SCENE_NODE_H__
#define __SCENE_NODE_H__

#include <vector>
#include <memory>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>


class SceneNode: public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    typedef std::unique_ptr<SceneNode> pointer_type;

public:
    SceneNode();

    void attachChild(pointer_type child);
    pointer_type detachChild(const SceneNode& node);

    void update(sf::Time deltaTime);

    sf::Transform getWorldTransform() const;
    sf::Vector2f getWorldPosition() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void updateCurrent(sf::Time deltaTime);
    virtual void updateChildren(sf::Time deltaTime);

private:
    std::vector<pointer_type> _children;
    SceneNode* _parent;
};


#endif//__SCENE_NODE_H__
