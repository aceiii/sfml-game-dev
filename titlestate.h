#ifndef __TITLE_STATE_H__
#define __TITLE_STATE_H__

#include "state.h"


class TitleState: public State {
public:
    TitleState(StateStack &stateStack, Context context);

    virtual void draw() override;
    virtual bool update(sf::Time deltaTime) override;
    virtual bool handleEvent(const sf::Event &event) override;

private:
    sf::Sprite _backgroundSprite;
    sf::Text _text;

    bool _showText;
    sf::Time _textEffectTime;
};


#endif//__TITLE_STATE_H__
