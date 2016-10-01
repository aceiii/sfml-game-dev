#include <cassert>
#include <algorithm>

#include "statestack.h"
#include "easylogging++.h"


StateStack::StateStack(sf::RenderWindow &window, TextureHolder &textures, FontHolder &fonts, Player &player):
    _context(window, textures, fonts, player)
{
    LOG(INFO) << "Constructing state stack.";
}

void StateStack::update(const sf::Time &deltaTime) {
    std::for_each(_stack.begin(), _stack.end(), [&deltaTime] (std::unique_ptr<State>& state) {
        state->update(deltaTime);
    });
}

void StateStack::draw() {
    for (auto it = _stack.begin(); it != _stack.end(); it++) {
        (*it)->draw();
    }
}

void StateStack::handleEvent(const sf::Event &event) {
    for (auto it = _stack.begin(); it != _stack.end(); it++) {
        if (!(*it)->handleEvent(event)) {
            return;
        }
    }

    applyPendingChanges();
}

void StateStack::pushState(States::ID stateID) {
    LOG(DEBUG) << "Pushing state (" << stateID << ").";
    _pendingList.emplace_back(StateStack::Push, stateID);
}

void StateStack::popState() {
    LOG(DEBUG) << "Popping state.";
    _pendingList.emplace_back(StateStack::Pop, States::Game);
}

void StateStack::clearStates() {
    LOG(DEBUG) << "Clearing states.";
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
    for (auto it = _pendingList.begin(); it != _pendingList.end(); it++) {
        switch (it->action) {
        case Push:
            _stack.push_back(createState(it->stateID));
            break;
        case Pop:
            _stack.pop_back();
            break;
        case Clear:
            _stack.clear();
            break;
        }
    }
    _pendingList.clear();
}
