#ifndef __PARALLEL_TASK_H__
#define __PARALLEL_TASK_H__


class ParallelTask {
public:
    ParallelTask();

    void execute();
    bool isFinished() const;

    void setCompletion(float percent);
    float getCompletion() const;
};


#endif//__PARALLEL_TASK_H__
