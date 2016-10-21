#include <sstream>
#include "settingsstate.h"
#include "easylogging++.h"
#include "util.h"

SettingsState::SettingsState(StateStack &stack, State::Context context):
    State(stack, context),
    _guiContainer(),
    _backgroundSprite(),
    _bindingButtons(),
    _bindingLabels()
{
    sf::RenderWindow& window = *getContext().window;
    TextureHolder& textures = *getContext().textures;
    FontHolder& fonts = *getContext().fonts;

    _backgroundSprite.setTexture(textures.get(Textures::TitleScreen));
    _backgroundSprite.setTextureRect(window.getViewport(window.getView()));

    for (std::size_t i = 0; i < Player::ActionCount; i += 1) {
        Player::Action action = static_cast<Player::Action>(i);

        auto button = std::make_shared<GUI::Button>(fonts, textures);
        button->setPosition(100, 100 + (i * 65));
        button->setText(Player::actionToString(action));
        button->setToggle(true);

        auto label = std::make_shared<GUI::Label>("Label", fonts);
        label->setPosition(375, 125 + (i * 65));

        _bindingButtons[action] = button;
        _bindingLabels[action] = label;

        _guiContainer.pack(button);
        _guiContainer.pack(label);
    }
    updateLabels();

    auto backButton = std::make_shared<GUI::Button>(fonts, textures);
    backButton->setPosition(100, 375);
    backButton->setText("Back");
    backButton->setCallback([this] () {
        requestStackPop();
    });

    _guiContainer.pack(backButton);
}

void SettingsState::updateLabels()
{
    Player& player = *getContext().player;

    for (std::size_t i = 0; i < Player::ActionCount; i += 1) {
        Player::Action action = static_cast<Player::Action>(i);
        try {
            sf::Keyboard::Key key = player.getAssignedKey(action);
            if (_bindingLabels.find(action) != _bindingLabels.end()) {
                _bindingLabels[action]->setText(toString(key));
            }
        } catch (const std::range_error& e) {
            LOG(DEBUG) << "Removing label for action '" << Player::actionToString(action) << "'";
            _bindingLabels[action]->setText("");
        }
    }
}

std::string SettingsState::toString(const sf::Keyboard::Key &key) const {
    return keyToString(key);
}

bool SettingsState::handleEvent(const sf::Event &event)
{
    bool isKeyBinding = false;
    for (std::size_t i = 0; i < Player::ActionCount; i += 1) {
        Player::Action action = static_cast<Player::Action>(i);
        if (_bindingButtons[action]->isActive()) {
            isKeyBinding = true;
            if (event.type == sf::Event::KeyReleased) {
                Player& player = *getContext().player;
                sf::Keyboard::Key key = event.key.code;

                try {
                    sf::Keyboard::Key prevKey = player.getAssignedKey(action);

                    LOG(DEBUG) << "Removing previous key: '" << keyToString(key) << "'";
                    player.removeAssignedKey(prevKey);
                } catch (const std::range_error& e) {
                    LOG(DEBUG) << "Key not yet assigned.";
                }

                try {
                    Player::Action prevAction = player.getActionForKey(key);

                    LOG(DEBUG) << "Removing key for previous action: '" << Player::actionToString(prevAction) << "'";
                    player.removeAssignedKey(key);
                } catch (const std::range_error& e) {
                    LOG(DEBUG) << "No previous key assigned to action.";
                }

                player.assignKey(action, event.key.code);
                _bindingButtons[action]->deactivate();
                _bindingButtons[action]->select();
            }
            break;
        }
    }

    if (isKeyBinding) {
        LOG(DEBUG) << "isKeyBinding";
        updateLabels();
    } else {
        LOG(DEBUG) << "_guiContainer.handleEvent()";
        _guiContainer.handleEvent(event);
    }

    return false;
}

void SettingsState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(_backgroundSprite);
    window.draw(_guiContainer);
}

bool SettingsState::update(sf::Time deltaTime) {
    return false;
}
