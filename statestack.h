#ifndef __STATE_STACK_H__
#define __STATE_STACK_H__

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include <map>

#include "state.h"
#include "states.h"


class StateStack: private sf::NonCopyable
{
public:
    enum Action
    {
        Push,
        Pop,
        Clear,
    };

public:
    explicit StateStack(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);

    template <typename T>
    void registerState(States::ID stateID);

    void update(const sf::Time& deltaTime);
    void draw();
    void handleEvent(const sf::Event& event);

    void pushState(States::ID stateID);
    void popState();
    void clearStates();

    bool isEmpty() const;

private:
    State::pointer_type createState(States::ID stateID);
    void applyPendingChanges();

private:
    struct PendingChange
    {
        Action action;
        States::ID stateID;
    };

private:
    std::vector<State::pointer_type> _stack;
    std::vector<PendingChange> _pendingList;
    State::Context _context;
    std::map<States::ID, std::function<State::pointer_type()>> _factories;

};


#include "statestack.hpp"

#endif//__STATE_STACK_H__
