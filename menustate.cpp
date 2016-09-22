//
// Created by Borin Ouch on 2016-09-21.
//

#include "menustate.h"

MenuState::MenuState(StateStack &stateStack, State::Context context):
    State(stateStack, context)
{
}

void MenuState::draw() {

}

bool MenuState::update(sf::Time deltaTime) {
    return false;
}

bool MenuState::handleEvent(const sf::Event &event) {
    return false;
}

