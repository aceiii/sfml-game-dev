#include <cassert>
#include <algorithm>

#include "statestack.h"


StateStack::StateStack(State::Context context) {

}

void StateStack::update(const sf::Time &deltaTime) {
//    for (auto it = _stack.begin(); it != _stack.end(); it++) {
//        if (!(*it)->update(deltaTime)) {
//            return;
//        }
//    }


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
    _stack.push_back(createState(stateID));
}

void StateStack::popState() {
    _stack.pop_back();
}

void StateStack::clearStates() {
    _stack.clear();
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
