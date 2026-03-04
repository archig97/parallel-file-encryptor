#pragma once
#include <vector>
#include "Task.h"

class TaskQueue {
public:
    TaskQueue(const std::vector<Task>& tasks);
    void dispatch(int numWorkers);

private:
    std::vector<Task> tasks;
};