#include <cassert>

#include "scenenode.h"
#include "category.h"
#include "command.h"
#include "util.h"
#include "commandqueue.h"

SceneNode::SceneNode() {
}

void SceneNode::attachChild(pointer_type child) {
    child->_parent = this;
    _children.push_back(std::move(child));
}

SceneNode::pointer_type SceneNode::detachChild(const SceneNode& node) {
    auto found = std::find_if(_children.begin(), _children.end(),
            [&](pointer_type& p) -> bool { return p.get() == &node; });

    assert(found != _children.end());

    pointer_type result = std::move(*found);
    result->_parent  = nullptr;
    _children.erase(found);
    return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawCurrent(target, states);

    for (auto it = _children.begin(); it != _children.end(); it++) {
        (*it)->draw(target, states);
    }
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
}

void SceneNode::update(sf::Time dt, CommandQueue& commands) {
    updateCurrent(dt, commands);
    updateChildren(dt, commands);
}

void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands) {
}

void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands) {
    for (auto it = _children.begin(); it != _children.end(); it++) {
        (*it)->update(dt, commands);
    }
}

sf::Transform SceneNode::getWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;
    for (const SceneNode* node = this; node != nullptr; node = node->_parent) {
        transform = node->getTransform() * transform;
    }
    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const {
    return getWorldTransform() * sf::Vector2f();
}

unsigned int SceneNode::getCategory() const {
    return Category::None;
}

void SceneNode::onCommand(const Command &command, sf::Time deltaTime) {
    if (command.category & getCategory()) {
        command.action(*this, deltaTime);
    }

    for (auto it = _children.begin(); it != _children.end(); it++) {
        (*it)->onCommand(command, deltaTime);
    }
}

sf::FloatRect SceneNode::getBoundingRect() const {
    return sf::FloatRect();
}

void SceneNode::checkNodeCollision(SceneNode &node, std::set<SceneNode::pair_type> &collisionPairs) {
    if (this != &node && !isDestroyed() && !node.isDestroyed() && collision(*this, node)) {
        collisionPairs.insert(std::minmax(this, &node));
    }

    for (auto it = begin(_children); it != end(_children); it++) {
        (*it)->checkNodeCollision(node, collisionPairs);
    }
}

bool SceneNode::isDestroyed() const {
    return false;
}

void SceneNode::checkSceneCollision(SceneNode &sceneGraph, std::set<SceneNode::pair_type> &collisionPairs) {
    checkNodeCollision(sceneGraph, collisionPairs);

    for (auto it = begin(sceneGraph._children); it != end(sceneGraph._children); it++) {
        checkSceneCollision(**it, collisionPairs);
    }
}

bool SceneNode::isMarkedForRemoval() const {
    return isDestroyed();
}

void SceneNode::removeWrecks() {
    auto wreckfieldBegin = std::remove_if(begin(_children), end(_children), std::mem_fn(&SceneNode::isMarkedForRemoval));
    _children.erase(wreckfieldBegin, end(_children));

    std::for_each(begin(_children), end(_children), std::mem_fn(&SceneNode::removeWrecks));
}

