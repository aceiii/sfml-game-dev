#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    ~Game();

    void run();

private:
    void processEvents();
    void update();
    void render();

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:
    sf::RenderWindow _window;
    sf::CircleShape _player;

    bool _isMovingUp;
    bool _isMovingDown;
    bool _isMovingLeft;
    bool _isMovingRight;
};


#endif//__GAME_H__

