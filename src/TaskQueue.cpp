#include "../include/TaskQueue.h"
#include "../include/Worker.h"
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

TaskQueue::TaskQueue(const std::vector<Task>& tasks)
    : tasks(tasks) {}

void TaskQueue::dispatch(int numWorkers) {
    int taskIndex = 0;

    for (int i = 0; i < numWorkers; ++i) {
        pid_t pid = fork();

        if (pid == 0) { // Child
            Worker worker;
            worker.process(tasks, i, numWorkers);
            exit(0);
        }
    }

    // Parent waits
    for (int i = 0; i < numWorkers; ++i) {
        wait(nullptr);
    }
}//
// Created by Archismita Ghosh on 3/4/26.
//