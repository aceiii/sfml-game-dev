#include "button.h"


GUI::Button::Button(const FontHolder &fonts, const TextureHolder &textures) {
    _sprite.setTexture(_normalTexture);
    _text.setPosition(sf::Vector2f(_normalTexture.getSize() / 2u));
}

GUI::Button::~Button() {

}

bool GUI::Button::isSelectable() const {
    return true;
}

void GUI::Button::select() {
    Component::select();
    _sprite.setTexture(_selectedTexture);
}

void GUI::Button::deselect() {
    Component::deselect();
    _sprite.setTexture(_normalTexture);
}

void GUI::Button::activate() {
    Component::activate();

    if (_isToggle) {
        _sprite.setTexture(_pressedTexture);
    }

    if (_callback) {
        _callback();
    }

    if (!_isToggle) {
        deactivate();
    }
}

void GUI::Button::deactivate() {
    Component::deactivate();

    if (_isToggle) {
        if (isSelected()) {
            _sprite.setTexture(_selectedTexture);
        } else {
            _sprite.setTexture(_normalTexture);
        }
    }
}

void GUI::Button::setText(const std::string &text) {
    _text.setString(text);
}

void GUI::Button::setCallback(GUI::Button::function func) {
    _callback = func;
}

void GUI::Button::handleEvent(const sf::Event &event) {

}
