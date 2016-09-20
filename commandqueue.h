//
// Created by Borin Ouch on 2016-09-20.
//

#ifndef __COMMAND_QUEUE_H__
#define __COMMAND_QUEUE_H__


#include <queue>

#include "command.h"


class CommandQueue
{
public:
    void push(const Command& command);
    Command pop();
    bool isEmpty() const;

private:
    std::queue<Command> _queue;
};


#endif//__COMMAND_QUEUE_H__
