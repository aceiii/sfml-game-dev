#include "component.h"

GUI::Component::Component() {
}

GUI::Component::~Component() {
}

bool GUI::Component::isSelected() const {
    return false;
}

void GUI::Component::select() {

}

void GUI::Component::deselect() {

}

bool GUI::Component::isActive() const {
    return false;
}

void GUI::Component::activate() {

}

void GUI::Component::deactivate() {

}

void GUI::Component::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(*this, states);
}
