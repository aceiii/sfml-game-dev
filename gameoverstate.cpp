#include "gameoverstate.h"

GameOverState::GameOverState(StateStack &stateStack, Context context):
    State(stateStack, context),
    _text()
{
    sf::View view = getContext().window->getView();

    _text.setFont(getContext().fonts->get(Fonts::Default));
    _text.setCharacterSize(36);
    _text.setString("Game Over!");
    _text.setPosition(view.getCenter());
}

void GameOverState::draw() {
    getContext().window->draw(_text);
}

bool GameOverState::update(sf::Time deltaTime) {
    return false;
}

bool GameOverState::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyReleased) {
        requestStateClear();
        requestStackPush(States::Menu);
    }

    return false;
}
