#include "io.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace io {
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