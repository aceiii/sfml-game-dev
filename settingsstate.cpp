#include <sstream>
#include "settingsstate.h"
#include "button.h"
#include "label.h"

SettingsState::SettingsState(StateStack &stack, State::Context context):
    State(stack, context), _guiContainer()
{
    _backgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

    _bindingButtons[Player::MoveLeft] = std::make_shared<GUI::Button>(*getContext().fonts, *getContext().textures);

    _bindingLabels[Player::MoveLeft] = std::make_shared<GUI::Label>("Move Left", *getContext().fonts);

    updateLabels();

    auto backButton = std::make_shared<GUI::Button>(*getContext().fonts, *getContext().textures);
    backButton->setPosition(100, 375);
    backButton->setText("Back");
    backButton->setCallback([this] () {
        requestStackPop();
    });

    _guiContainer.pack(_bindingButtons[Player::MoveLeft]);
    _guiContainer.pack(_bindingLabels[Player::MoveLeft]);
}

void SettingsState::updateLabels()
{
    Player& player = *getContext().player;

    for (std::size_t i = 0; i < Player::ActionCount; i += 1) {
        Player::Action action = static_cast<Player::Action>(i);
        sf::Keyboard::Key key = player.getAssignedKey(action);
        _bindingLabels[action]->setText(toString(key));
    }
}

std::string SettingsState::toString(const sf::Keyboard::Key &key) const {
    switch (key) {
        case sf::Keyboard::Unknown: return "Unknown";
        case sf::Keyboard::A: return "A";
        case sf::Keyboard::B: return "B";
        case sf::Keyboard::C: return "C";
        case sf::Keyboard::D: return "D";
        case sf::Keyboard::E: return "E";
        case sf::Keyboard::F: return "F";
        case sf::Keyboard::G: return "G";
        case sf::Keyboard::H: return "H";
        case sf::Keyboard::I: return "I";
        case sf::Keyboard::J: return "J";
        case sf::Keyboard::K: return "K";
        case sf::Keyboard::L: return "L";
        case sf::Keyboard::M: return "M";
        case sf::Keyboard::N: return "N";
        case sf::Keyboard::O: return "O";
        case sf::Keyboard::P: return "P";
        case sf::Keyboard::Q: return "Q";
        case sf::Keyboard::R: return "R";
        case sf::Keyboard::S: return "S";
        case sf::Keyboard::T: return "T";
        case sf::Keyboard::U: return "U";
        case sf::Keyboard::V: return "V";
        case sf::Keyboard::W: return "W";
        case sf::Keyboard::X: return "X";
        case sf::Keyboard::Y: return "Y";
        case sf::Keyboard::Z: return "Z";
        case sf::Keyboard::Num0: return "0";
        case sf::Keyboard::Num1: return "1";
        case sf::Keyboard::Num2: return "2";
        case sf::Keyboard::Num3: return "3";
        case sf::Keyboard::Num4: return "4";
        case sf::Keyboard::Num5: return "5";
        case sf::Keyboard::Num6: return "6";
        case sf::Keyboard::Num7: return "7";
        case sf::Keyboard::Num8: return "8";
        case sf::Keyboard::Num9: return "9";
        case sf::Keyboard::Escape: return "ESC";
        case sf::Keyboard::LControl: return "L-CTRL";
        case sf::Keyboard::LShift: return "L-SHIFT";
        case sf::Keyboard::LAlt: return "L-ALT";
        case sf::Keyboard::LSystem: return "L-SYS";
        case sf::Keyboard::RControl: return "R-CTRL";
        case sf::Keyboard::RShift: return "R-SHIFT";
        case sf::Keyboard::RAlt: return "R-ALT";
        case sf::Keyboard::RSystem: return "R-SYS";
        case sf::Keyboard::Menu: return "MENU";
        case sf::Keyboard::LBracket: return "[";
        case sf::Keyboard::RBracket: return "]";
        case sf::Keyboard::SemiColon: return ";";
        case sf::Keyboard::Comma: return ",";
        case sf::Keyboard::Period: return ".";
        case sf::Keyboard::Quote: return "'";
        case sf::Keyboard::Slash: return "/";
        case sf::Keyboard::BackSlash: return "\\";
        case sf::Keyboard::Tilde: return "~";
        case sf::Keyboard::Equal: return "=";
        case sf::Keyboard::Dash: return "-";
        case sf::Keyboard::Space: return "SPACE";
        case sf::Keyboard::Return: return "RETURN";
        case sf::Keyboard::BackSpace: return "BACK";
        case sf::Keyboard::Tab: return "TAB";
        case sf::Keyboard::PageUp: return "PGUP";
        case sf::Keyboard::PageDown: return "PGDN";
        case sf::Keyboard::End: return "END";
        case sf::Keyboard::Home: return "HOME";
        case sf::Keyboard::Insert: return "INS";
        case sf::Keyboard::Delete: return "DEL";
        case sf::Keyboard::Add: return "ADD";
        case sf::Keyboard::Subtract: return "SUB";
        case sf::Keyboard::Multiply: return "MUL";
        case sf::Keyboard::Divide: return "DIV";
        case sf::Keyboard::Left: return "LEFT";
        case sf::Keyboard::Right: return "RIGHT";
        case sf::Keyboard::Up: return "UP";
        case sf::Keyboard::Down: return "DOWN";
        case sf::Keyboard::Numpad0: return "NUM0";
        case sf::Keyboard::Numpad1: return "NUM1";
        case sf::Keyboard::Numpad2: return "NUM2";
        case sf::Keyboard::Numpad3: return "NUM3";
        case sf::Keyboard::Numpad4: return "NUM4";
        case sf::Keyboard::Numpad5: return "NUM5";
        case sf::Keyboard::Numpad6: return "NUM6";
        case sf::Keyboard::Numpad7: return "NUM7";
        case sf::Keyboard::Numpad8: return "NUM8";
        case sf::Keyboard::Numpad9: return "NUM9";
        case sf::Keyboard::F1: return "F1";
        case sf::Keyboard::F2: return "F2";
        case sf::Keyboard::F3: return "F3";
        case sf::Keyboard::F4: return "F4";
        case sf::Keyboard::F5: return "F5";
        case sf::Keyboard::F6: return "F6";
        case sf::Keyboard::F7: return "F7";
        case sf::Keyboard::F8: return "F8";
        case sf::Keyboard::F9: return "F9";
        case sf::Keyboard::F10: return "F10";
        case sf::Keyboard::F11: return "F11";
        case sf::Keyboard::F12: return "F12";
        case sf::Keyboard::F13: return "F13";
        case sf::Keyboard::F14: return "F14";
        case sf::Keyboard::F15: return "F15";
        case sf::Keyboard::Pause: return "Pause";
        default: return "Unknown";
    }
}

bool SettingsState::handleEvent(const sf::Event &event)
{
    bool isKeyBinding = false;
    for (std::size_t i = 0; i < Player::ActionCount; i += 1) {
        Player::Action action = static_cast<Player::Action>(i);
        if (_bindingButtons[action]->isActive()) {
            isKeyBinding = true;
            if (event.type == sf::Event::KeyReleased) {
                getContext().player->assignKey(action, event.key.code);
                _bindingButtons[action]->deactivate();
            }
            break;
        }
    }

    if (isKeyBinding) {
        updateLabels();
    } else {
        _guiContainer.handleEvent(event);
    }

    return false;
}


