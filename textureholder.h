#ifndef __TEXTURE_HOLDER_H__
#define __TEXTURE_HOLDER_H__


#include "resourceholder.h"
#include "textures.h"

#include <SFML/Graphics/Texture.hpp>


typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;


#endif//__TEXTURE_HOLDER_H__
