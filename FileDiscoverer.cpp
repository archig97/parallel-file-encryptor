#include "FileDiscoverer.h"
#include <filesystem>

namespace fs = std::filesystem;

std::vector<Task> FileDiscoverer::discover(const std::string& root, TaskType type) {
    std::vector<Task> tasks;

    for (const auto& entry : fs::recursive_directory_iterator(root)) {

        if (entry.path().extension() == ".enc")
            continue;
        if (entry.is_regular_file()) {
            tasks.push_back(Task{type, entry.path().string()});
        }
    }

    return tasks;
}//
// Created by Archismita Ghosh on 3/4/26.
//