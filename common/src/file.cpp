#include "common/file.h"
#include <fstream>
#include <iostream>
#include <sstream>

namespace file {
    std::string readAsString(std::string_view path) {
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

    std::vector<std::vector<int>> readAsColumns(std::string_view path) {
        std::ifstream inputFile(path);
        if (!inputFile) {
            std::cerr << "Error opening file " << path << std::endl;
            return {};
        }

        std::vector<std::vector<int>> columns;

        std::string line;
        while (std::getline(inputFile, line)) {
            std::stringstream ss(line);

            int num;
            size_t columnIndex = 0;
            while (ss >> num) {
                if (columnIndex < columns.size()) {
                    columns[columnIndex].push_back(num);
                } else {
                    columns.push_back({num});
                }
                columnIndex++;
            }
        }

        return columns;
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