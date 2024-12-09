#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

namespace file {
    std::string readAsString(std::string_view path);
    std::vector<std::vector<int>> readAsColumns(std::string_view path);

    std::vector<int> readNumbers(std::string_view path);

    template <typename T>
    std::vector<std::vector<T>> readAsRows(std::string_view path) {
        std::ifstream inputFile(path);
        if (!inputFile) {
            std::cerr << "Error opening file " << path << std::endl;
            return {};
        }

        std::vector<std::vector<T>> rows;
        std::string line;
        while (std::getline(inputFile, line)) {
            if (line.empty()) {
                continue;  // Skip empty lines
            }

            std::stringstream ss(line);

            T num;
            std::vector<T> row;
            while (ss >> num) {
                row.push_back(num);
            }
            rows.push_back(row);
        }

        return rows;
    }
}
