#include "label.h"

using namespace GUI;

Label::Label(const std::string& text, const FontHolder& fonts):
    _text(text, fonts.get(Fonts::Label), 16)
{
}

bool Label::isSelectable() const
{
    return false;
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_text, states);
}

void Label::setText(const std::string& text)
{
    _text.setString(text);
}

