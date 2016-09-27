#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "menustate.h"
#include "util.h"

MenuState::MenuState(StateStack &stateStack, State::Context context):
    State(stateStack, context)
{
    sf::Font& font = getContext().fonts->get(Fonts::Default);

    sf::Text playOption;
    playOption.setFont(font);
    playOption.setString("Play");
    centerOrigin(playOption);

    playOption.setPosition(context.window->getView().getSize() / 2.0f);

    _options.push_back(playOption);
}

void MenuState::draw() {

}

bool MenuState::update(sf::Time deltaTime) {
    return false;
}

bool MenuState::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            if (_optionIndex > 0) {
                _optionIndex -= 1;
            } else {
                _optionIndex = _options.size() - 1;
            }

            updateOptionText();
        } else if (event.key.code == sf::Keyboard::Down) {
            if (_optionIndex < _options.size() - 1) {
                _optionIndex += 1;
            } else {
                _optionIndex = 0;
            }

            updateOptionText();
        }

        if (event.key.code == sf::Keyboard::Return) {
            if (_optionIndex == Play) {
                requestStackPop();
                requestStackPush(States::Game);
            } else if (_optionIndex == Exit) {
                requestStackPop();
            }
        }
    }

    return true;
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
