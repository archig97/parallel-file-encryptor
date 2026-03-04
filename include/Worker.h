#pragma once
#include <vector>
#include "Task.h"

class Worker {
public:
    void process(const std::vector<Task> &tasks, int workerId, int totalWorkers, const std::string &outputDir);
};