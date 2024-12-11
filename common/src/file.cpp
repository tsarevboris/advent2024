#include "common/file.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace file {
    std::string readString(std::string_view path) {
        std::ifstream inputFile(path);
        if (!inputFile) {
            std::cerr << "Error opening file " << path << std::endl;
            return {};
        }

        std::string fileContents;
        std::string line;
        while (std::getline(inputFile, line)) {
            fileContents += line + '\n';
        }

        return fileContents;
    }

    std::vector<int> readDigits(std::string_view path) {
        std::ifstream inputFile(path);
        if (!inputFile) {
            std::cerr << "Error opening file " << path << std::endl;
            return {};
        }

        std::vector<int> digits;
        char digit;
        while (inputFile >> digit) {
            if ('0' <= digit && digit <= '9') {
                digits.push_back(digit - '0');
            }
        }

        return digits;
    }
}