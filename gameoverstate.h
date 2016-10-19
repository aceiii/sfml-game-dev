#ifndef __GAME_OVER_STATE_H__
#define __GAME_OVER_STATE_H__

#include "state.h"


class GameOverState: public State {
public:
    GameOverState(StateStack& stateStack, Context context);

    virtual void draw() override;
    virtual bool update(sf::Time deltaTime) override;
    virtual bool handleEvent(const sf::Event &event) override;

private:
    sf::Text _text;
};


#endif//__GAME_OVER_STATE_H__
