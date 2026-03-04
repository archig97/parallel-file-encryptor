#pragma once
#include <vector>
#include <string>
#include "Task.h"

class FileDiscoverer {
public:
    static std::vector<Task> discover(const std::string& root, TaskType type);
};