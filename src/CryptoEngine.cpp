#include "../include/CryptoEngine.h"
#include <fstream>
#include <stdexcept>
#include <cstdlib>

CryptoEngine::CryptoEngine() {
    const char* envKey = std::getenv("ENCRYPTION_KEY");
    if (!envKey) {
        throw std::runtime_error("ENCRYPTION_KEY not set");
    }
    key = envKey;
}

void CryptoEngine::encryptFile(const std::string& path) {
    transform(path, path + ".enc", true);
}

void CryptoEngine::decryptFile(const std::string& path) {
    transform(path, path + ".dec", false);
}

void CryptoEngine::transform(const std::string& input,
                             const std::string& output,
                             bool encrypt) {
    std::ifstream in(input, std::ios::binary);
    if (!in)
        throw std::runtime_error("Cannot open input file");

    std::ofstream out(output, std::ios::binary);
    if (!out)
        throw std::runtime_error("Cannot open output file");

    char buffer[4096];
    size_t keyLen = key.size();

    while (in.read(buffer, sizeof(buffer)) || in.gcount()) {
        std::streamsize count = in.gcount();

        for (int i = 0; i < count; ++i) {
            buffer[i] ^= key[i % keyLen]; // XOR symmetric cipher
        }

        out.write(buffer, count);
    }
}//
// Created by Archismita Ghosh on 3/4/26.
//