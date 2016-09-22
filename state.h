#ifndef __STATE_H__
#define __STATE_H__

#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "states.h"
#include "player.h"
#include "textureholder.h"
#include "fontholder.h"


class StateStack;

class State {
public:
    typedef std::unique_ptr<State> pointer_type;

    struct Context
    {
        Context() {}
        Context(sf::RenderWindow& window, TextureHolder& textureHolder, FontHolder& fontHolder, Player& player):
            window(&window),textures(&textureHolder),fonts(&fontHolder),player(&player) {}

        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
        Player* player;
    };

public:
    State();
    virtual ~State();

    virtual void draw() = 0;
    virtual bool update(sf::Time deltaTime) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;

protected:
    void requestStackPush(States::ID stateID);
    void requestStackPop();
    void requestStateClear();

    Context getContext() const;

private:
    StateStack* _stack;
    Context _context;

};


#endif//__STATE_H__
