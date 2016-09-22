#include "titlestate.h"

TitleState::TitleState(StateStack &stateStack, State::Context context):
    State(stateStack, context)
{
}

void TitleState::draw() {

}

bool TitleState::update(sf::Time deltaTime) {
    return false;
}

bool TitleState::handleEvent(const sf::Event &event) {
    return false;
}
