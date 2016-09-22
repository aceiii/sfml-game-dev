#include "application.h"
#include "titlestate.h"
#include "menustate.h"
#include "gamestate.h"
#include "pausestate.h"

void Application::registerStates() {
    _stateStack.registerState<TitleState>(States::Title);
    _stateStack.registerState<MenuState>(States::Menu);
    _stateStack.registerState<GameState>(States::Game);
    _stateStack.registerState<PauseState>(States::Pause);
}

void Application::processInput() {
    sf::Event event;
    while (_window.pollEvent(event)) {
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
