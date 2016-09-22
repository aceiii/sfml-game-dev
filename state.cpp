#include "state.h"


State::State(StateStack& stateStack, Context context):
    _stack(&stateStack),_context(context)
{
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
