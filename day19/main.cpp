#include <iostream>
#include "common/file.h"

bool isSubstring(const std::string& design, const std::string& pattern, size_t start, size_t end) {
    return design.substr(start, end - start + 1) == pattern;
}

bool isPossible(const std::vector<std::string>& patterns, const std::string& design, size_t pos, std::vector<int>& memo) {
    if (pos >= design.size()) {
        return true;
    }

    if (memo[pos] != -1) {
        return memo[pos];
    }

    for (const auto& pattern : patterns) {
        if (isSubstring(design, pattern, pos, pos + pattern.size() - 1)) {
            if (isPossible(patterns, design, pos + pattern.size(), memo)) {
                return memo[pos] = true;
            }
        }
    }

    return memo[pos] = false;
}

// Wrapper Function
bool isPossible(const std::vector<std::string>& patterns, const std::string& design) {
    std::vector<int> memo(design.size(), -1);
    return isPossible(patterns, design, 0, memo);
}

long long countPossibilities(const std::vector<std::string>& patterns, const std::string& design, size_t pos, std::vector<long long>& memo) {
    if (patterns.empty()) {
        return 0;
    }

    if (pos >= design.size()) {
        return 1; // Found a valid way to complete the design
    }

    if (memo[pos] != -1) {
        return memo[pos];
    }

    long long totalWays = 0;

    for (const auto& pattern : patterns) {
        if (pattern.size() > design.size() - pos) {
            continue;
        }

        if (pos + pattern.size() <= design.size() &&
            isSubstring(design, pattern, pos, pos + pattern.size() - 1)) {
            // Count possibilities from this position onward
            totalWays += countPossibilities(patterns, design, pos + pattern.size(), memo);
        }
    }

    memo[pos] = totalWays;
    return totalWays;
}

// Wrapper function
long long countAllPossibilities(const std::vector<std::string>& patterns, const std::string& design) {
    std::vector<long long> memo(design.size(), -1);
    return countPossibilities(patterns, design, 0, memo);
}

void task1() {
    std::ifstream inputFile("input.txt");

    std::vector<std::string> patterns;
    std::vector<std::string> designs;

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }
        if (patterns.empty()) {
            size_t pos = 0;
            while (pos < line.size()) {
                auto commaPos = line.find(", ", pos);
                if (commaPos == std::string::npos) {
                    commaPos = line.size();
                }
                patterns.push_back(line.substr(pos, commaPos - pos));
                pos = commaPos + 2;
            }
        } else {
            designs.push_back(line);
        }
    }

    long long possibleCount = 0;
    for (size_t i = 0; i < designs.size(); i++) {
        if (isPossible(patterns, designs[i])) {
            possibleCount++;
        }
    }
    std::cout << "Possible designs: " << possibleCount << std::endl;
}

void task2() {
    std::ifstream inputFile("input.txt");

    std::vector<std::string> patterns;
    std::vector<std::string> designs;

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue;
        }
        if (patterns.empty()) {
            size_t pos = 0;
            while (pos < line.size()) {
                auto commaPos = line.find(", ", pos);
                if (commaPos == std::string::npos) {
                    commaPos = line.size();
                }
                patterns.push_back(line.substr(pos, commaPos - pos));
                pos = commaPos + 2;
            }
        } else {
            designs.push_back(line);
        }
    }

    long long possibleSum = 0;
    for (size_t i = 0; i < designs.size(); i++) {
        possibleSum += countAllPossibilities(patterns, designs[i]);
    }
    std::cout << "All possibilities: " << possibleSum << std::endl;
}

int main() {
    std::cout << "Task 1: " << std::endl;
    task1(); // 206
    std::cout << "-----------" << std::endl;

    std::cout << "Task 2: " << std::endl;
    task2(); // 622121814629343
    std::cout << "-----------" << std::endl;
    return 0;
}
