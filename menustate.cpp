#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "easylogging++.h"
#include "menustate.h"
#include "util.h"
#include "button.h"

MenuState::MenuState(StateStack &stateStack, State::Context context):
    State(stateStack, context)
{
    auto playButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
    playButton->setPosition(100, 250);
    playButton->setText("Play");
    playButton->setCallback([this] () {
        requestStackPop();
        requestStackPush(States::Game);
    });

    _guiContainer.pack(playButton);
}

void MenuState::draw() {
    sf::RenderWindow& window =  *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(_backgroundSprite);
    window.draw(_guiContainer);
}

bool MenuState::update(sf::Time deltaTime) {
    return true;
}

bool MenuState::handleEvent(const sf::Event &event) {
    _guiContainer.handleEvent(event);
    return false;
}

void MenuState::updateOptionText() {
    if (_options.empty()) {
        return;
    }

    for (auto it = _options.begin(); it != _options.end(); it++) {
        //it->setColor(sf::Color::White);

        it->setFillColor(sf::Color::White);
        it->setOutlineColor(sf::Color::White);
    }

//    _options[_optionIndex].setColor(sf::Color::Red);

    _options[_optionIndex].setFillColor(sf::Color::Red);
    _options[_optionIndex].setOutlineColor(sf::Color::Red);
}
