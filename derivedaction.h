#ifndef __DERIVED_ACTION_H__
#define __DERIVED_ACTION_H__

#include <functional>
#include <cassert>

#include <SFML/System/Time.hpp>


class SceneNode;

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn) {
    return [=] (SceneNode& node, sf::Time dt) {
        assert(dynamic_cast<GameObject*>(&node) != nullptr);

        fn(static_cast<GameObject&>(node), dt);
    };
};


#endif//__DERIVED_ACTION_H__
