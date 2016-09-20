//
// Created by Borin Ouch on 2016-09-20.
//

#include "commandqueue.h"

void CommandQueue::push(const Command &command) {
    _queue.push(command);
}

Command CommandQueue::pop() {
    Command command = _queue.front();
    _queue.pop();
    return command;
}

bool CommandQueue::isEmpty() const {
    return _queue.empty();
}
