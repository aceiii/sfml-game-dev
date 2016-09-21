#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <SFML/Window/Event.hpp>
#include <map>

#include "commandqueue.h"


class Player
{
public:
    enum Action
    {
        MoveLeft,
        MoveRight,
    };

    Player();

    void assignKey(Action action, sf::Keyboard::Key key);
    sf::Keyboard::Key getAssignedKey(Action action) const;

    void handleEvent(const sf::Event& event, CommandQueue& commands);
    void handleRealtimeInput(CommandQueue& commands);

private:
    static bool isRealtimeAction(Action action);

private:
    std::map<sf::Keyboard::Key, Action> _keyBinding;
    std::map<Action, Command> _actionBinding;

    const float playerSpeed = 30.0f;
};


#endif//__PLAYER_H__
