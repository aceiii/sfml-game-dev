#include "loadingstate.h"
#include "util.h"

LoadingState::LoadingState(StateStack &stateStack, State::Context context):
    State(stateStack, context)
{
    sf::RenderWindow& window = *context.window;
    sf::Font& font = context.fonts->get(Fonts::Default);

    _loadingText.setFont(font);
    _loadingText.setString("Loading Resources");
    centerOrigin(_loadingText);
    _loadingText.setPosition(window.getSize().x / 2u, window.getSize().y / 2u + 50);

    _progressBarBackground.setFillColor(sf::Color::White);
    _progressBarBackground.setSize(sf::Vector2f(window.getSize().x - 20, 10));
    _progressBarBackground.setPosition(10, _loadingText.getPosition().y + 40);

    _progressBar.setFillColor(sf::Color(100, 100, 100));
    _progressBar.setSize(sf::Vector2f(200, 10));
    _progressBar.setPosition(10, _loadingText.getPosition().y + 40);

    setCompletion(0.0f);

    _loadingTask.execute();
}

void LoadingState::draw() {

}

bool LoadingState::update(sf::Time deltaTime) {
    return false;
}

bool LoadingState::handleEvent(const sf::Event &event) {
    return false;
}

