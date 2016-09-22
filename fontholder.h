#ifndef __FONT_HOLDER_H__
#define __FONT_HOLDER_H__

#include <SFML/Graphics/Font.hpp>

#include "resourceholder.h"
#include "fonts.h"


typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;


#endif//__FONT_HOLDER_H__
