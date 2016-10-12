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
    return false;
}

bool GameState::handleEvent(const sf::Event &event) {
    sf::RenderWindow& window = *getContext().window;
    CommandQueue& commands = _world.getCommandQueue();

    _player.handleEvent(event, commands);
    _player.handleRealtimeInput(commands);

    return false;
}
