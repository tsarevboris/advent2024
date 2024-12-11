#include <iostream>
#include "common/file.h"
#include <vector>
#include <string>
#include <map>

int countPaths(const std::vector<std::vector<char>>& data, char symbol, int i, int j, std::map<std::pair<int, int>, bool>& visited) {
    if (i < 0 || j < 0 || i >= static_cast<int>(data.size()) || j >= static_cast<int>(data[i].size())) {
        return 0;
    }

    if (data[i][j] != symbol) {
        return 0;
    }

    if (symbol == '9') {
        if (visited.find({i, j}) != visited.end()) {
            return 0;
        } else {
            visited[{i, j}] = true;
            return 1;
        }
    }

    const auto nextSymbol = static_cast<char>(symbol + 1);
    int sum = countPaths(data, nextSymbol, i + 1, j, visited) +
           countPaths(data, nextSymbol, i - 1, j, visited) +
           countPaths(data, nextSymbol, i, j + 1, visited) +
           countPaths(data, nextSymbol, i, j - 1, visited);

    if (symbol == '0') {
        std::cout << "Sum: " << sum << std::endl;
    }
    return sum;
}

int countPaths2(const std::vector<std::vector<char>>& data, char symbol, int i, int j) {
    if (i < 0 || j < 0 || i >= static_cast<int>(data.size()) || j >= static_cast<int>(data[i].size())) {
        return 0;
    }

    if (data[i][j] != symbol) {
        return 0;
    }

    if (symbol == '9') {
        return 1;
    }

    const auto nextSymbol = static_cast<char>(symbol + 1);
    int sum = countPaths2(data, nextSymbol, i + 1, j) +
              countPaths2(data, nextSymbol, i - 1, j) +
              countPaths2(data, nextSymbol, i, j + 1) +
              countPaths2(data, nextSymbol, i, j - 1);

    if (symbol == '0') {
        std::cout << "Sum: " << sum << std::endl;
    }
    return sum;
}

void task1() {
    const auto data = file::readRows<char>("input.txt");
    std::cout << "Data: " << std::endl;
    for (const auto& row : data) {
        for (const auto& num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    int pathsCount = 0;
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data[i].size(); j++) {
            std::map<std::pair<int, int> , bool> visited;
            pathsCount += countPaths(data, '0', static_cast<int>(i), static_cast<int>(j), visited);
        }
    }
    std::cout << "Paths count: " << pathsCount << std::endl;
}

void task2() {
    const auto data = file::readRows<char>("input.txt");
    std::cout << "Data: " << std::endl;
    for (const auto& row : data) {
        for (const auto& num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }

    int pathsCount = 0;
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data[i].size(); j++) {
            pathsCount += countPaths2(data, '0', static_cast<int>(i), static_cast<int>(j));
        }
    }
    std::cout << "Paths count: " << pathsCount << std::endl;
}

int main() {
//    task1();
    task2();
    return 0;
}
