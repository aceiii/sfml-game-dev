#include <cassert>
#include <string>

#include "game.h"
#include "resourcepath.h"


Game::Game():
    _window(sf::VideoMode(640, 480), "MY Game!"),
    _world(_window),
    _isPaused(false)
{
}

Game::~Game()
{
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (_window.isOpen()) {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();

            if (!_isPaused) {
                update(TimePerFrame);
            }
        }
        render();
    }
}

void Game::processEvents()
{
    CommandQueue& commands = _world.getCommandQueue();

    sf::Event event;
    while (_window.pollEvent(event)) {
        _player.handleEvent(event, commands);

        switch (event.type) {
        case sf::Event::GainedFocus:
            _isPaused = false;
            break;
        case sf::Event::LostFocus:
            _isPaused = true;
            break;
        case sf::Event::Closed:
            _window.close();
            break;
        }
    }

    _player.handleRealtimeInput(commands);
}

void Game::render()
{
    _window.clear();
    //_window.draw(_player);
    _world.draw();


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

    //_player.move(movement * deltaTime.asSeconds());
    _world.update(deltaTime);
}
