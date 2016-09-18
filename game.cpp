
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
    sf::Clock clock;
    while (_window.isOpen()) {
        sf::Time deltaTime = clock.restart();

        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            _window.close();
            break;
        }
    }
}

void Game::render()
{
    _window.clear();
    _window.draw(_player);
    _window.display();
}

void Game::update(sf::Time deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);

    if (_isMovingUp) {
        movement.y -= PlayerSpeed;
    }
    if (_isMovingDown) {
        movement.y += PlayerSpeed;
    }
    if (_isMovingLeft) {
        movement.x -= PlayerSpeed;
    }
    if (_isMovingRight) {
        movement.x += PlayerSpeed;
    }

    _player.move(movement * deltaTime.asSeconds());
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W) {
        _isMovingUp = isPressed;
    } else if (key == sf::Keyboard::S) {
        _isMovingDown = isPressed;
    } else if (key == sf::Keyboard::A) {
        _isMovingLeft = isPressed;
    } else if (key == sf::Keyboard::D) {
        _isMovingRight = isPressed;
    }
}

