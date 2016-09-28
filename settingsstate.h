#ifndef __SETTINGS_STATE_H__
#define __SETTINGS_STATE_H__

#include "state.h"
#include "container.h"
#include "button.h"
#include "label.h"


class SettingsState: public State
{
public:
    SettingsState(StateStack& stack, Context context);

    virtual bool handleEvent(const sf::Event& event);

private:
    void updateLabels();
    std::string toString(const sf::Keyboard::Key& key) const;

private:
    sf::Sprite _backgroundSprite;

    GUI::Container _guiContainer;

    std::map<Player::Action, std::shared_ptr<GUI::Button>> _bindingButtons;
    std::map<Player::Action, std::shared_ptr<GUI::Label>> _bindingLabels;

};


#endif//__SETTINGS_STATE_H__
