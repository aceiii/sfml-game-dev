#ifndef __MENU_STATE_H__
#define __MENU_STATE_H__

#include "state.h"


class MenuState: public State
{
public:
    MenuState(StateStack &stateStack, Context context);

    virtual void draw() override;
    virtual bool update(sf::Time deltaTime) override;
    virtual bool handleEvent(const sf::Event &event) override;
};


#endif//__MENU_STATE_H__
