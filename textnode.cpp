#include "textnode.h"
#include "util.h"

TextNode::TextNode(const FontHolder &fonts, const std::string &text):
    _text()
{
    _text.setFont(fonts.get(Fonts::Main));
    _text.setCharacterSize(20);
    setString(text);
}

void TextNode::setString(const std::string &text) {
    _text.setString(text);
    centerOrigin(_text);
}

void TextNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_text, states);
}
