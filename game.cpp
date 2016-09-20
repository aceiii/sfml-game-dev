
#include <cassert>
#include <string>

#include "game.h"

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif//__APPLE__

namespace {
    std::string getBundlePath() {
#ifdef __APPLE__
        CFBundleRef mainBundle = CFBundleGetMainBundle();
        CFURLRef resourceUrl = CFBundleCopyResourcesDirectoryURL(mainBundle);
        char path[PATH_MAX];
        if (!CFURLGetFileSystemRepresentation(resourceUrl, TRUE, (UInt8*)path, PATH_MAX)) {
            return "";
        }
        CFRelease(resourceUrl);
        return std::string(path) + "/";
#else
        return "";
#endif//__APPLE__
    }

    std::string resourcePath(const std::string& path) {
        return getBundlePath() + path;
    }
}

Game::Game():
    _window(sf::VideoMode(640, 480), "MY Game!"),
    _world(_window)
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
            update(TimePerFrame);
        }
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

