#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include "common/file.h"

bool isSafe(const std::vector<int>& numbers) {
    if (numbers.size() < 2) {
        return true;
    }

    if (numbers[0] == numbers[1]) {
        return false;
    }

    bool increasing = numbers[0] < numbers[1];
    for (size_t i = 0; i < numbers.size() - 1; i++) {
        const auto diff = numbers[i] - numbers[i + 1];
        if ((increasing && (diff < -3 || -1 < diff)) || (!increasing && (diff < 1 || 3 < diff))) {
            return false;
        }
    }
    return true;
}

bool isSafe2(const std::vector<int>& numbers) {
    if (isSafe(numbers)) {
        return true;
    }

    for (size_t i = 0; i < numbers.size(); i++) {
        auto numbers2 = numbers;
        numbers2.erase(numbers2.begin() + i);
        if (isSafe(numbers2)) {
            return true;
        }
    }

    return false;
}


void task1() {
    const auto table = file::readTable<int>("input.txt");

    const auto safeCount = std::accumulate(table.cbegin(), table.cend(), 0, [](int acc, const auto& row) {
        return acc + isSafe(row);
    });

    std::cout << "Safe count 1: " << safeCount << std::endl;
}

void task2() {
    const auto table = file::readTable<int>("input.txt");

    const auto safeCount = std::accumulate(table.cbegin(), table.cend(), 0, [](int acc, const auto& row) {
        return acc + isSafe2(row);
    });

    std::cout << "Safe count 2: " << safeCount << std::endl;
}

int main() {
    task1(); // 269
    task2(); // 337
}
