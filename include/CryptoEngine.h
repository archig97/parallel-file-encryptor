#pragma once
#include <string>

class CryptoEngine {
public:
    CryptoEngine();
    void encryptFile(const std::string &inputPath, const std::string &outputDir);
    void decryptFile(const std::string& path);

private:
    void transform(const std::string& input,
                   const std::string& output,
                   bool encrypt);

    std::string key;
};