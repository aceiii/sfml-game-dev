#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <functional>
#include <SFML/System/Time.hpp>


class SceneNode;


struct Command
{
    std::function<void(SceneNode&, sf::Time)> action;
    unsigned int category;

    Command():action(nullptr),category(0) {}
};


#endif//__COMMAND_H__
