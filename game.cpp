
#include "game.h"

Game::Game():_window(sf::VideoMode(640, 480), "MY Game!"),_player()
{
    _player.setRadius(40.0f);
    _player.setPosition(100.0f, 100.0f);
    _player.setFillColor(sf::Color::Cyan);
}

Game::~Game()
{
}

void Game::run()
{
    while (_window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
    }
}

void Game::render()
{
    _window.clear();
    _window.draw(_player);
    _window.display();
}

void Game::update()
{
}

