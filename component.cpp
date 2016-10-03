#include "component.h"

GUI::Component::Component():
    _isActive(false),_isSelected(false)
{
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
    return _isActive;
}

void GUI::Component::activate() {
    _isActive = true;
}

void GUI::Component::deactivate() {
    _isActive = false;
}
