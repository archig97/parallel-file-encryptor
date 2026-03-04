#include "Worker.h"
#include "CryptoEngine.h"
#include <iostream>
#include <unistd.h>



void Worker::process(const std::vector<Task>& tasks, int workerId, int totalWorkers) {
    CryptoEngine engine;

    for (size_t i = workerId; i < tasks.size(); i += totalWorkers) {
        const Task& task = tasks[i];
        std::cout << "[Worker " << workerId << "] PID " << getpid()
            << " processing: " << task.filepath << std::endl;

        try {
            if (task.type == TaskType::Encrypt)
                engine.encryptFile(task.filepath);
            else
                engine.decryptFile(task.filepath);
        } catch (const std::exception& e) {
            std::cerr << "Worker error on file "
                      << task.filepath << ": "
                      << e.what() << "\n";
        }
    }
}//
// Created by Archismita Ghosh on 3/4/26.
//