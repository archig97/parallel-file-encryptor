cmake_minimum_required(VERSION 3.16)
project(ParallelEncryptor)

set(CMAKE_CXX_STANDARD 17)

add_executable(encryptor
        src/main.cpp
        src/FileDiscoverer.cpp
        src/TaskQueue.cpp
        src/CryptoEngine.cpp
        src/Worker.cpp
        src/FileDiscoverer.cpp
        src/TaskQueue.cpp
        src/Worker.cpp
        src/CryptoEngine.cpp
        include/Task.h
        include/FileDiscoverer.h
        include/TaskQueue.h
        include/Worker.h
        include/CryptoEngine.h
)