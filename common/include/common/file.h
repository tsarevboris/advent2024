#pragma once

#include "common/table.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

namespace file {
    std::string readString(std::string_view path);
    std::vector<int> readDigits(std::string_view path);

    template<typename T>
    Table<T> readTable(std::string_view path) {
        std::ifstream inputFile(path);
        if (!inputFile) {
            std::cerr << "Error opening file " << path << std::endl;
            return {};
        }

        Table<T> table;
        std::string line;
        while (std::getline(inputFile, line)) {
            if (line.empty()) {
                continue;  // Skip empty lines
            }

            std::stringstream ss(line);

            T value;
            std::vector<T> row;
            while (ss >> value) {
                row.push_back(value);
            }
            table.data.push_back(std::move(row));
        }

        return table;
    }

    template <typename T>
    std::vector<std::vector<T>> readRows(std::string_view path) {
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
            rows.push_back(std::move(row));
        }

        return rows;
    }

    template <typename T>
    std::vector<std::vector<T>> readColumns(std::string_view path){
        std::ifstream inputFile(path);
        if (!inputFile) {
            std::cerr << "Error opening file " << path << std::endl;
            return {};
        }

        std::vector<std::vector<T>> columns;
        columns.reserve(2); // Adjust if needed

        std::string line;
        while (std::getline(inputFile, line)) {
            if (line.empty()) {
                continue;  // Skip empty lines
            }

            std::stringstream ss(line);

            T num;
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
}
