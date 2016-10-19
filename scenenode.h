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
#include <set>

#include "command.h"


class SceneNode: public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
    typedef std::unique_ptr<SceneNode> pointer_type;
    typedef std::pair<SceneNode*, SceneNode*> pair_type;

public:
    SceneNode();

    void attachChild(pointer_type child);
    pointer_type detachChild(const SceneNode& node);

    void update(sf::Time deltaTime);

    virtual bool isDestroyed() const;
    virtual bool isMarkedForRemoval() const;
    void removeWrecks();

    sf::Transform getWorldTransform() const;
    sf::Vector2f getWorldPosition() const;
    virtual sf::FloatRect getBoundingRect() const;

    virtual unsigned int getCategory() const;

    void onCommand(const Command& command, sf::Time deltaTime);

    void checkNodeCollision(SceneNode& node, std::set<pair_type>& collisionPairs);
    void checkSceneCollision(SceneNode& sceneGraph, std::set<pair_type>& collisionPairs);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void updateCurrent(sf::Time deltaTime);
    virtual void updateChildren(sf::Time deltaTime);

private:
    std::vector<pointer_type> _children;
    SceneNode* _parent;

    bool _destroyed;
};


#endif//__SCENE_NODE_H__
