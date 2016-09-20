#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/Graphics.hpp>

#include "world.h"


class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
    sf::RenderWindow _window;

    World _world;

    bool _isMovingUp;
    bool _isMovingDown;
    bool _isMovingLeft;
    bool _isMovingRight;

    const float PlayerSpeed = 32.0f;
    const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
};


#endif//__GAME_H__

