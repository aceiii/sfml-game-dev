#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SFML/Window/Event.hpp>

#include "commandqueue.h"


class Player
{
public:
    void handleEvent(const sf::Event& event, CommandQueue& commands);
    void handleRealtimeInput(CommandQueue& commands);
};


#endif//__PLAYER_H__
