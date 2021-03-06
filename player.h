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
        MoveUp,
        MoveDown,
        Fire,
        LaunchMissile,
        ActionCount,
    };

    static std::string actionToString(Action action);

    Player();

    void assignKey(Action action, sf::Keyboard::Key key);
    void removeAssignedKey(sf::Keyboard::Key key);
    sf::Keyboard::Key getAssignedKey(Action action) const;
    Action getActionForKey(sf::Keyboard::Key key) const;

    void handleEvent(const sf::Event& event, CommandQueue& commands);
    void handleRealtimeInput(CommandQueue& commands);

private:
    void initializeActions();

    static bool isRealtimeAction(Action action);

private:
    std::map<sf::Keyboard::Key, Action> _keyBinding;
    std::map<Action, Command> _actionBinding;

    const float playerSpeed = 30.0f;
};


#endif//__PLAYER_H__
