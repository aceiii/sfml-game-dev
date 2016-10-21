//
// Created by Borin Ouch on 2016-09-21.
//

#include "pausestate.h"

PauseState::PauseState(StateStack &stateStack, State::Context context):
    State(stateStack, context),
    _pausedText(),
    _instructionText()
{
    sf::Font& font = getContext().fonts->get(Fonts::Default);

    _pausedText.setFont(font);
    _pausedText.setCharacterSize(18);
    _pausedText.setFillColor(sf::Color::White);
    _pausedText.setString("- PAUSED -");

    _instructionText.setFont(font);
    _instructionText.setCharacterSize(12);
    _instructionText.setFillColor(sf::Color(255,255,255,190));
    _instructionText.setString("Press the BACKSPACE key to exit.");
}

void PauseState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));

    window.draw(backgroundShape);
    window.draw(_pausedText);
    window.draw(_instructionText);

}

bool PauseState::update(sf::Time deltaTime) {
    return false;
}

bool PauseState::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::BackSpace) {
            requestStateClear();
            requestStackPush(States::Menu);
        }
    }

    return false;
}
