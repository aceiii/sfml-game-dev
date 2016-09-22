#ifndef __PAUSE_STATE_H__
#define __PAUSE_STATE_H__

#include "state.h"


class PauseState: public State
{
public:
    PauseState(StateStack &stateStack, Context context);

    virtual void draw() override;

    virtual bool update(sf::Time deltaTime) override;

    virtual bool handleEvent(const sf::Event &event) override;
};


#endif//__PAUSE_STATE_H__
