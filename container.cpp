#include "container.h"
#include "easylogging++.h"
#include "util.h"

using namespace GUI;

Container::Container():_children(),_selectedChild(-1)
{
}

Container::~Container()
{
}

void Container::pack(Component::pointer_type component)
{
    _children.push_back(component);
    if (!hasSelection() && component->isSelectable()) {
        select(_children.size() - 1);
    }
}

bool Container::isSelectable() const
{
    return false;
}

void Container::handleEvent(const sf::Event& event)
{
    if (hasSelection() && _children[_selectedChild]->isActive()) {
        _children[_selectedChild]->handleEvent(event);
    } else if (event.type == sf::Event::KeyReleased) {
        LOG(DEBUG) << "Container.handleEvent() - " << keyToString(event.key.code);
        if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
            selectPrevious();
        } else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
            selectNext();
        } else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) {
            if (hasSelection()) {
                LOG(DEBUG) << "Activate child at " << _selectedChild;
                _children[_selectedChild]->activate();
            }
        }
    }
}

void Container::select(std::size_t index)
{
    LOG(INFO) << "Container.select(" << index << ")";

    if (_children[index]->isSelectable()) {
        if (hasSelection()) {
            _children[_selectedChild]->deselect();
        }
        _children[index]->select();
        _selectedChild = index;
    }
}

void Container::selectNext()
{
    LOG(INFO) << "Container.selectNext()";

    if (!hasSelection()) {
        return;
    }

    int next = _selectedChild;
    do {
        next = (next + 1) % _children.size();
    } while (!_children[next]->isSelectable());
    select(next);
}

void Container::selectPrevious()
{
    LOG(INFO) << "Container.selectPrevious()";

    if (!hasSelection()) {
        return;
    }

    int prev = _selectedChild;
    do {
        prev = (prev - 1) % _children.size();
    } while (!_children[prev]->isSelectable());
    select(prev);
}

bool Container::hasSelection()
{
    return _selectedChild < _children.size();
}

void Container::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    for (auto it = _children.begin(); it != _children.end(); it++) {
        pointer_type child = *it;
        target.draw(*child, states);
    }
}

