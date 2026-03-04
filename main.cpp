#include "FileDiscoverer.h"
#include "TaskQueue.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cout << "Usage: ./encryptor <encrypt|decrypt> <directory> <workers>\n";
        return 1;
    }

    std::string mode = argv[1];
    std::string directory = argv[2];
    int workers = std::stoi(argv[3]);

    TaskType type;

    if (mode == "encrypt")
        type = TaskType::Encrypt;
    else if (mode == "decrypt")
        type = TaskType::Decrypt;
    else {
        std::cerr << "Invalid mode\n";
        return 1;
    }

    auto tasks = FileDiscoverer::discover(directory, type);

    TaskQueue queue(tasks);
    queue.dispatch(workers);

    return 0;
}