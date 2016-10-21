#include <cassert>
#include <algorithm>

#include "statestack.h"
#include "easylogging++.h"


StateStack::StateStack(sf::RenderWindow &window, TextureHolder &textures, FontHolder &fonts, Player &player):
    sf::NonCopyable(),
    _stack(),
    _pendingList(),
    _factories(),
    _context(window, textures, fonts, player)
{
    LOG(INFO) << "Constructing state stack.";
}

void StateStack::update(const sf::Time &deltaTime) {
    for (auto it = begin(_stack); it != end(_stack); it++) {
        if (!(*it)->update(deltaTime)) {
            break;
        }
    }

    applyPendingChanges();
}

void StateStack::draw() {
    for (auto it = _stack.begin(); it != _stack.end(); it++) {
        (*it)->draw();
    }
}

void StateStack::handleEvent(const sf::Event &event) {
    for (auto it = rbegin(_stack); it != rend(_stack); it++) {
        if (!(*it)->handleEvent(event)) {
            break;
        }
    }

    applyPendingChanges();
}

void StateStack::pushState(States::ID stateID) {
    LOG(DEBUG) << "Queuing State Push (" << stateID << ").";
    _pendingList.emplace_back(StateStack::Push, stateID);
}

void StateStack::popState() {
    LOG(DEBUG) << "Queuing State Pop.";
    _pendingList.emplace_back(StateStack::Pop, States::Game);
}

void StateStack::clearStates() {
    LOG(DEBUG) << "Queuing State Clear.";
    _pendingList.emplace_back(StateStack::Clear, States::Game);
}

bool StateStack::isEmpty() const {
    return _stack.empty();
}

State::pointer_type StateStack::createState(States::ID stateID) {
    auto found = _factories.find(stateID);
    assert(found != _factories.end());

    return found->second();
}

void StateStack::applyPendingChanges() {
    for (auto pendingChange: _pendingList) {
        switch (pendingChange.action) {
        case Push:
            LOG(DEBUG) << "Pushing state (" << pendingChange.stateID << ").";
            _stack.push_back(createState(pendingChange.stateID));
            break;
        case Pop:
            LOG(DEBUG) << "Popping state.";
            _stack.pop_back();
            break;
        case Clear:
            LOG(DEBUG) << "Clearing state.";
            _stack.clear();
            break;
        }
    }
    _pendingList.clear();
}
