#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SFML/Graphics/RenderWindow.hpp>

#include "statestack.h"


class Application
{
public:
    void registerStates();

    void update(sf::Time deltaTime);
    void draw();
    void processInput();

private:
    sf::RenderWindow _window;
    StateStack _stateStack;
};


#endif//__APPLICATION_H__
