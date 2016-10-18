#include <sstream>
#include <complex>
#include "util.h"

std::string keyToString(const sf::Keyboard::Key& key) {
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

float toRadians(float deg) {
    return static_cast<float>(M_PI / 180.0 * deg);
}

double toRadians(double deg) {
    return M_PI / 180 * deg;
}

float toDegrees(float rads) {
    return static_cast<float>(rads * 180.0 * M_PI);
}

double toDegrees(double rads) {
    return rads * 180.0 * M_PI;
}

sf::Vector2f unitVector(sf::Vector2f pos) {
    float dist = std::sqrt(pos.x * pos.x + pos.y * pos.y);

    pos.x /= dist;
    pos.y /= dist;

    return pos;
}

float distance(const SceneNode &node1, const SceneNode &node2) {
    sf::Vector2f vec = node1.getWorldPosition() - node2.getWorldPosition();
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

bool collision(const SceneNode &lhs, const SceneNode &rhs) {
    return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

bool matchesCategories(SceneNode::pair_type &colliders, Category::Type type1, Category::Type type2) {
    unsigned int category1 = colliders.first->getCategory();
    unsigned int category2 = colliders.second->getCategory();

    if (type1 & category1 && type2 & category2) {
        return true;
    } else if (type1 & category2 && type2 & category1) {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    return false;
}
