#include "../include/FileDiscoverer.h"
#include <filesystem>

namespace fs = std::filesystem;

std::vector<Task> FileDiscoverer::discover(const std::string& root, TaskType type) {
    if (!std::filesystem::exists(root)) {
        throw std::runtime_error("Directory does not exist: " + root);
    }

    std::vector<Task> tasks;

    for (const auto& entry : fs::recursive_directory_iterator(root)) {
        if (!entry.is_regular_file())
            continue;

        std::string path = entry.path().string();

        if (type == TaskType::Encrypt) {
            // Skip files that are already encrypted
            if (entry.path().extension() == ".enc" || entry.path().extension() == ".dec")
                continue;
        }

        if (type == TaskType::Decrypt) {
            // Only decrypt encrypted files
            if (entry.path().extension() != ".enc")
                continue;
        }

        tasks.push_back(Task{type, path});
    }

    return tasks;
}