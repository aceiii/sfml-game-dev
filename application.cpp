#include "application.h"
#include "titlestate.h"
#include "menustate.h"
#include "gamestate.h"
#include "pausestate.h"

Application::Application():
    _window(sf::VideoMode(640, 480), "The Game!"),
    _stateStack(_window, _textures, _fonts, _player)
{
    registerStates();

    _stateStack.pushState(States::Menu);
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (_window.isOpen()) {
        processInput();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processInput();
            update(TimePerFrame);
        }
        draw();
    }
}

void Application::registerStates() {
    _stateStack.registerState<TitleState>(States::Title);
    _stateStack.registerState<MenuState>(States::Menu);
    _stateStack.registerState<GameState>(States::Game);
    _stateStack.registerState<PauseState>(States::Pause);
}

void Application::processInput() {
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
            continue;
        }

        _stateStack.handleEvent(event);
    }
}

void Application::update(sf::Time deltaTime) {
    _stateStack.update(deltaTime);
}

void Application::draw() {
    _window.clear();
    _stateStack.draw();
    _window.display();
}
