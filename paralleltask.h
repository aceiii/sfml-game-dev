#ifndef __PARALLEL_TASK_H__
#define __PARALLEL_TASK_H__

#include <SFML/System/Thread.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Mutex.hpp>


class ParallelTask {
public:
    ParallelTask();

    void execute();
    bool isFinished();
    float getCompletion();

private:
    void runTask();

private:
    sf::Thread _thread;
    bool _finished;
    sf::Clock _elapsedTime;
    sf::Mutex _mutex;

};


#endif//__PARALLEL_TASK_H__
