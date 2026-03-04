#pragma once
#include <string>

enum class TaskType {
    Encrypt,
    Decrypt
};

struct Task {
    TaskType type;
    std::string filepath;
};//
// Created by Archismita Ghosh on 3/4/26.
//

