#include "application.h"
#include "titlestate.h"
#include "menustate.h"
#include "gamestate.h"
#include "pausestate.h"
#include "resourcepath.h"
#include "easylogging++.h"

Application::Application():
    _window(sf::VideoMode(640, 480), "The Game!"),
    _stateStack(_window, _textures, _fonts, _player)
{
    registerMedia();
    registerStates();

    _stateStack.pushState(States::Menu);
}

void Application::run()
{
    LOG(INFO) << "Starting game loop.";

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

void Application::registerMedia() {

    LOG(INFO) << "Loading fonts.";
    _fonts.load(Fonts::Default, resourcePath("media/fonts/arial.ttf"));
    _fonts.load(Fonts::Label, resourcePath("media/fonts/arial.ttf"));

    LOG(INFO) << "Loading textures.";
    _textures.load(Textures::Desert, resourcePath("media/textures/desert.png"));
    _textures.load(Textures::Raptor, resourcePath("media/textures/raptor.png"));
    _textures.load(Textures::Eagle, resourcePath("media/textures/eagle.png"));
    _textures.load(Textures::ButtonNormal, resourcePath("media/textures/button-normal.png"));
    _textures.load(Textures::ButtonPressed, resourcePath("media/textures/button-pressed.png"));
    _textures.load(Textures::ButtonSelected, resourcePath("media/textures/button-selected.png"));
    _textures.load(Textures::TitleScreen, resourcePath("media/textures/title-bg.png"));
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
