#ifndef __MENU_STATE_H__
#define __MENU_STATE_H__

#include "state.h"
#include "container.h"


class MenuState: public State
{
public:
    MenuState(StateStack &stateStack, Context context);

    virtual void draw() override;
    virtual bool update(sf::Time deltaTime) override;

    virtual bool handleEvent(const sf::Event &event) override;

private:
    void updateOptionText();

private:
    enum OptionNames
    {
        Play,
        Exit,
    };

    std::vector<sf::Text> _options;
    std::size_t _optionIndex;

    GUI::Container _guiContainer;
    sf::Sprite _backgroundSprite;
};


#endif//__MENU_STATE_H__
