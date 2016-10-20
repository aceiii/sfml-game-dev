#include "gamestate.h"

GameState::GameState(StateStack &stateStack, State::Context context):
    State(stateStack, context),_world(context),_player(*context.player)
{
}

void GameState::draw() {
    _world.draw();
}

bool GameState::update(sf::Time deltaTime) {
    _world.update(deltaTime);

    CommandQueue& commands = _world.getCommandQueue();
    _player.handleRealtimeInput(commands);

    return true;
}

bool GameState::handleEvent(const sf::Event &event) {
    CommandQueue& commands = _world.getCommandQueue();

    _player.handleEvent(event, commands);
    //_player.handleRealtimeInput(commands);

    return true;
}
