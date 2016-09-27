#ifndef __LOADING_STATE_H__
#define __LOADING_STATE_H__

#include "state.h"
#include "paralleltask.h"


class LoadingState: public State
{
public:
    LoadingState(StateStack &stateStack, Context context);

    virtual void draw() override;
    virtual bool update(sf::Time deltaTime) override;
    virtual bool handleEvent(const sf::Event &event) override;

private:
    sf::Text _loadingText;
    sf::RectangleShape _progressBarBackground;
    sf::RectangleShape _progressBar;
    ParallelTask _loadingTask;

};


#endif//__LOADING_STATE_H__
