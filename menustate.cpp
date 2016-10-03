#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "easylogging++.h"
#include "menustate.h"
#include "util.h"
#include "button.h"

MenuState::MenuState(StateStack &stateStack, State::Context context):
    State(stateStack, context)
{
    FontHolder& fonts = *getContext().fonts;
    TextureHolder& textures = *getContext().textures;
    sf::RenderWindow& window = *getContext().window;

    _backgroundSprite.setTexture(textures.get(Textures::TitleScreen));
    _backgroundSprite.setTextureRect(window.getViewport(window.getView()));

    auto playButton = std::make_shared<GUI::Button>(fonts, textures);
    playButton->setPosition(150, 250);
    playButton->setText("Play");
    playButton->setCallback([this] () {
        LOG(DEBUG) << "Play button handler called.";
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto settingsButton = std::make_shared<GUI::Button>(fonts, textures);
    settingsButton->setPosition(150, 315);
    settingsButton->setText("Settings");
    settingsButton->setCallback([this] () {
        LOG(DEBUG) << "Going to settings.";
        requestStackPush(States::Settings);
    });

    auto exitButton = std::make_shared<GUI::Button>(fonts, textures);
    exitButton->setPosition(150, 380);
    exitButton->setText("Exit");
    exitButton->setCallback([this] () {
        LOG(DEBUG) << "Exit handler called.";
        requestStateClear();
    });

    _guiContainer.pack(playButton);
    _guiContainer.pack(settingsButton);
    _guiContainer.pack(exitButton);
}

void MenuState::draw() {
    sf::RenderWindow& window =  *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(_backgroundSprite);
    window.draw(_guiContainer);
}

bool MenuState::update(sf::Time deltaTime) {
    return true;
}

bool MenuState::handleEvent(const sf::Event &event) {
    _guiContainer.handleEvent(event);
    return false;
}

void MenuState::updateOptionText() {
    if (_options.empty()) {
        return;
    }

    for (auto it = _options.begin(); it != _options.end(); it++) {
        //it->setColor(sf::Color::White);

        it->setFillColor(sf::Color::White);
        it->setOutlineColor(sf::Color::White);
    }

//    _options[_optionIndex].setColor(sf::Color::Red);

    _options[_optionIndex].setFillColor(sf::Color::Red);
    _options[_optionIndex].setOutlineColor(sf::Color::Red);
}
