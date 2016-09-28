#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <SFML/Graphics/RenderWindow.hpp>

#include "easylogging++.h"
#include "statestack.h"


class Application
{
public:
    Application();

    void run();

protected:
    void registerStates();

    void update(sf::Time deltaTime);
    void draw();
    void processInput();

private:
    const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);

    sf::RenderWindow _window;
    TextureHolder _textures;
    FontHolder _fonts;
    Player _player;

    StateStack _stateStack;

};


#endif//__APPLICATION_H__
