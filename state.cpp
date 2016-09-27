#include "state.h"
#include "statestack.h"

State::State(StateStack& stateStack, Context context):
    _stack(&stateStack),_context(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID) {
    _stack->pushState(stateID);
}

void State::requestStackPop() {
    _stack->popState();
}

void State::requestStateClear() {
    _stack->clearStates();
}

State::Context State::getContext() const {
    return State::Context();
}
