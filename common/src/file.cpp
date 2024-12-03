#include "common/file.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace file {
    std::string readFileAsString(std::string_view path) {
        std::ifstream inputFile(path);
        if (!inputFile) {
            std::cerr << "Error opening file!" << std::endl;
            return {};
        }

        std::string fileContents;
        std::string line;
        while (std::getline(inputFile, line)) {
            fileContents += line + '\n';
        }

        return fileContents;
    }

    std::vector<std::vector<int>> readFileAsVectorOfVectors(std::string_view path) {
        std::ifstream inputFile(path);
        if (!inputFile) {
            std::cerr << "Error opening file!" << std::endl;
            return {};
        }

        std::vector<std::vector<int>> allNumbers;

        std::string line;
        while (std::getline(inputFile, line)) {
            if (line.empty()) {
                continue;  // Skip empty lines
            }

            std::stringstream ss(line);
            std::vector<int> lineNumbers;
            lineNumbers.reserve(10);  // Reserve space for expected numbers, adjust if needed

            int num;
            while (ss >> num) {
                lineNumbers.push_back(num);
            }

            if (!lineNumbers.empty()) {
                allNumbers.push_back(std::move(lineNumbers));
            }
        }

        return allNumbers;
    }
}