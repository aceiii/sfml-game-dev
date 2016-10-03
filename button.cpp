#include "button.h"
#include "util.h"
#include "easylogging++.h"

GUI::Button::Button(const FontHolder &fonts, const TextureHolder &textures):
    _normalTexture(textures.get(Textures::ButtonNormal)),
    _selectedTexture(textures.get(Textures::ButtonSelected)),
    _pressedTexture(textures.get(Textures::ButtonPressed))
{
    _sprite.setTexture(_normalTexture);

    _text.setFont(fonts.get(Fonts::Button));
    _text.setPosition(sf::Vector2f(_normalTexture.getSize() / 2u));

    _isToggle = false;
}

GUI::Button::~Button() {

}

bool GUI::Button::isSelectable() const {
    return true;
}

void GUI::Button::select() {
    LOG(INFO) << "Button (" << _text.getString().toAnsiString() << ")" << " selected.";
    Component::select();
    _sprite.setTexture(_selectedTexture);
}

void GUI::Button::deselect() {
    LOG(INFO) << "Button (" << _text.getString().toAnsiString() << ")" << " deselected.";
    Component::deselect();
    _sprite.setTexture(_normalTexture);
}

void GUI::Button::activate() {
    LOG(INFO) << "Button.activate() - " << _text.getString().toAnsiString();

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
    LOG(INFO) << "Button.deactivate() - " << _text.getString().toAnsiString();

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

    updateText();
}

void GUI::Button::setCallback(GUI::Button::function func) {
    _callback = func;
}

void GUI::Button::handleEvent(const sf::Event &event) {

}

void GUI::Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    target.draw(_sprite, states);
    target.draw(_text, states);
}

void GUI::Button::updateText() {
    sf::FloatRect bounds = _text.getLocalBounds();
    _text.setOrigin(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);
}

void GUI::Button::setToggle(bool toggle) {
    _isToggle = toggle;
}
