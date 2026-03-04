#pragma once
#include <vector>
#include "Task.h"

class TaskQueue {
public:
    TaskQueue(const std::vector<Task>& tasks);
    void dispatch(int numWorkers, const std::string& outputDir);

private:
    std::vector<Task> tasks;
};