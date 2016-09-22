#include "state.h"


State::State():_context() {

}

State::~State() {

}

void State::requestStackPush(States::ID stateID) {

}

void State::requestStackPop() {

}

void State::requestStateClear() {

}

State::Context State::getContext() const {
    return State::Context();
}
