#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "io.h"

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
        if (increasing && (diff < -3 || -1 < diff)) {
            return false;
        } else if (!increasing && (diff < 1 || 3 < diff)) {
            return false;
        }
    }
    return true;
}

bool isSafe2(const std::vector<int>& numbers) {
    if (isSafe(numbers)) {
        return true;
    }

    for (int i = 0; i < numbers.size(); i++) {
        auto numbers2 = numbers;
        numbers2.erase(numbers2.begin() + i);
        if (isSafe(numbers2)) {
            return true;
        }
    }

    return false;
}


void task1() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::vector<int> numbers;
    int safeNumber = 0;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        int num;
        while (ss >> num) {
            numbers.push_back(num);
        }

        if (isSafe(numbers)) {
            safeNumber++;
        }
        numbers.clear();
    }
    inputFile.close();

    std::cout << "Safe numbers: " << safeNumber << std::endl;
}

void task2() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::vector<int> numbers;
    int safeNumber = 0;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        int num;
        while (ss >> num) {
            numbers.push_back(num);
        }

        if (isSafe2(numbers)) {
            safeNumber++;
        }
        numbers.clear();
    }
    inputFile.close();

    std::cout << "Safe numbers: " << safeNumber << std::endl;
}

int main() {
    task1();
    task2();
}
