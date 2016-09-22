#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include "state.h"
#include "world.h"


class GameState: public State
{
public:
    GameState(StateStack &stateStack, Context context);

    virtual void draw() override;
    virtual bool update(sf::Time deltaTime) override;
    virtual bool handleEvent(const sf::Event &event) override;

private:
    World _world;
    Player& _player;

};


#endif//__GAME_STATE_H__
