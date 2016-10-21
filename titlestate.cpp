#include "titlestate.h"

TitleState::TitleState(StateStack &stateStack, State::Context context):
    State(stateStack, context),
    _backgroundSprite(),
    _text(),
    _showText(false),
    _textEffectTime(sf::Time::Zero)
{
}

void TitleState::draw() {

}

bool TitleState::update(sf::Time deltaTime) {
    _textEffectTime += deltaTime;

    if (_textEffectTime >= sf::seconds(0.5f)) {
        _showText = !_showText;
        _textEffectTime = sf::Time::Zero;
    }

    return true;
}

bool TitleState::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        requestStackPop();
        requestStackPush(States::Menu);
    }

    return true;
}
