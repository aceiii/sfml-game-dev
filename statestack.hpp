#ifndef __STATE_STACK_IMPL_H__
#define __STATE_STACK_IMPL_H__


template<typename T>
void StateStack::registerState(States::ID stateID) {
    _factories[stateID] = [this] () {
        return State::pointer_type(new T(*this, _context));
    };
}


#endif //__STATE_STACK_IMPL_H__
