//
// Created by Borin Ouch on 2016-09-21.
//

#include "pausestate.h"

PauseState::PauseState(StateStack &stateStack, State::Context context):
    State(stateStack, context)
{
}

void PauseState::draw() {

}

bool PauseState::update(sf::Time deltaTime) {
    return false;
}

bool PauseState::handleEvent(const sf::Event &event) {
    return false;
}
