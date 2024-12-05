#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "common/file.h"
#include "common/parse.h"

void readAsRows(std::string_view path, std::map<int, std::vector<int>>& rules, std::vector<std::vector<int>>& numbers) {
    std::ifstream inputFile(path);
    if (!inputFile) {
        std::cerr << "Error opening file " << path << std::endl;
    }

    std::vector<std::vector<int>> allNumbers;

    std::string line;
    bool readingRules = true;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            readingRules = false;
            continue;
        }

        std::stringstream ss(line);

        size_t pos = 0;
        if (readingRules) {
            const auto key = parse::readNumberAndMove(line, pos, 2);
            pos++;
            const auto value = parse::readNumberAndMove(line, pos);
            rules[key.value()].push_back(value.value());
        } else {
            std::vector<int> update;
            while (true) {
                const auto number = parse::readNumberAndMove(line, pos);
                if (!number.has_value()) {
                    break;
                }
                update.push_back(number.value());

                if (!parse::checkCharAndMove(line, ',', pos)) {
                    break;
                }
            }
            numbers.push_back(update);
        }
    }
}

bool check(const std::map<int, std::vector<int>>& rules, const std::vector<int>& update) {
    for (size_t i = 0; i < update.size() - 1; i++) {
        const auto left = update[i];
        const auto right = update[i + 1];

        if (!rules.contains(right)) {
            continue;
        }

        const auto& range = rules.at(right);
        for (const auto value : range) {
            if (value == left) {
                return false;
            }
        }
    }
    return true;
}

void fixOrder(const std::map<int, std::vector<int>>& rules, std::vector<int>& update) {
    for (size_t i = 0; i < update.size() - 1; i++) {
        const auto left = update[i];
        const auto right = update[i + 1];

        if (!rules.contains(right)) {
            continue;
        }

        const auto& range = rules.at(right);
        for (const auto value : range) {
            if (value == left) {
                std::swap(update[i], update[i + 1]);
                return;
            }
        }
    }
}

int getMiddle(const std::vector<int>& range) {
    const auto pos = range.size() / 2;
    return range[pos];
}

void task1() {
    std::map<int, std::vector<int>> rules;
    std::vector<std::vector<int>> numbers;
    readAsRows("input.txt", rules, numbers);

    int sum = 0;
    for (const auto& update : numbers) {
        if (check(rules, update)) {
            sum += getMiddle(update);
        }
    }

    std::cout << "Sum: " << sum << std::endl;
}

void task2() {
    std::map<int, std::vector<int>> rules;
    std::vector<std::vector<int>> numbers;
    readAsRows("input.txt", rules, numbers);

    int sum = 0;
    for (auto& update : numbers) {
        if (!check(rules, update)) {
            while (!check(rules, update)) {
                fixOrder(rules, update);
            }
            sum += getMiddle(update);
        }
    }

    std::cout << "Sum: " << sum << std::endl;
}

int main() {
    task1();
    task2();
    return 0;
}
