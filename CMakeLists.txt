cmake_minimum_required(VERSION 3.16)
project(ParallelEncryptor)

set(CMAKE_CXX_STANDARD 17)

add_executable(encryptor
        main.cpp
        FileDiscoverer.cpp
        TaskQueue.cpp
        CryptoEngine.cpp
        Worker.cpp
        FileDiscoverer.cpp
        TaskQueue.cpp
        Worker.cpp
        CryptoEngine.cpp
        Task.h
        FileDiscoverer.h
        TaskQueue.h
        Worker.h
        CryptoEngine.h
)