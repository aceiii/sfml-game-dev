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

private:
    sf::RenderWindow _window;
    sf::CircleShape _player;
};


#endif//__GAME_H__

