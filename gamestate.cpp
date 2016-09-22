//
// Created by Borin Ouch on 2016-09-21.
//

#include "gamestate.h"

GameState::GameState(StateStack &stateStack, State::Context context):
    State(stateStack, context),_world(*context.window),_player(*context.player)
{
}

void GameState::draw() {

}

bool GameState::update(sf::Time deltaTime) {
    return false;
}

bool GameState::handleEvent(const sf::Event &event) {
    return false;
}
