#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

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

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
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

    return 0;
}

// clang++ -Wall -std=c++20 -Ilibs/ main.cpp -o build/main.a
