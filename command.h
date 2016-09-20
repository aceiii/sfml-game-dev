#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <functional>
#include <SFML/System/Time.hpp>

#include "scenenode.h"


struct Command
{
    std::function<void(SceneNode&, sf::Time)> action;
    unsigned int category;
};


#endif//__COMMAND_H__
