#ifndef __UTIL_H__
#define __UTIL_H__

#include <sstream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "scenenode.h"

template <typename T>
void centerOrigin(T& item) {
    sf::FloatRect bounds = item.getLocalBounds();
    item.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

template<typename T>
std::string toString(T t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

std::string keyToString(const sf::Keyboard::Key& key);

float toRadians(float deg);
double toRadians(double deg);

float toDegrees(float rads);
double toDegrees(double rads);

sf::Vector2f unitVector(sf::Vector2f pos);

float distance(const SceneNode& node1, const SceneNode& node2);

#endif//__UTIL_H__