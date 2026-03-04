#include "../include/FileDiscoverer.h"
#include "../include/TaskQueue.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 5) {
        std::cout << "Usage: ./encryptor <encrypt|decrypt> <input_dir> <output_dir> <workers>\n";
        return 1;
    }

    std::string mode = argv[1];
    std::string inputDir = argv[2];
    std::string outputDir = argv[3];
    int workers = std::stoi(argv[4]);

    TaskType type;

    if (mode == "encrypt")
        type = TaskType::Encrypt;
    else if (mode == "decrypt")
        type = TaskType::Decrypt;
    else {
        std::cerr << "Invalid mode\n";
        return 1;
    }

    auto tasks = FileDiscoverer::discover(inputDir, type);

    TaskQueue queue(tasks);
    queue.dispatch(workers, outputDir);

    return 0;
}