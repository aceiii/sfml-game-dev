#ifndef __UTIL_H__
#define __UTIL_H__


#include <SFML/Graphics/Rect.hpp>

template <typename T>
void centerOrigin(T& item) {
    sf::FloatRect bounds = item.getLocalBounds();
    item.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}


#endif//__UTIL_H__