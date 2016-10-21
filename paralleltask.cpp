#include <SFML/System/Lock.hpp>
#include "paralleltask.h"

ParallelTask::ParallelTask():
    _thread(&ParallelTask::runTask, this),
    _finished(false),
    _elapsedTime(),
    _mutex()
{
}

void ParallelTask::execute() {
}

bool ParallelTask::isFinished() {
    sf::Lock lock(_mutex);
    return _finished;
}

float ParallelTask::getCompletion() {
    return 0;
}

void ParallelTask::runTask() {
    // Dummy task - stall 10 seconds
    bool ended = false;
    while (!ended) {
        sf::Lock lock(_mutex);
        if (_elapsedTime.getElapsedTime().asSeconds() >= 10.0f) {
            ended = true;
        }
    }

    {
        sf::Lock lock(_mutex);
        _finished = true;
    }
}
