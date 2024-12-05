#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "common/parse.h"

void readRule(std::string_view line, std::map<int, std::vector<int>>& rules) {
    size_t pos = 0;
    const auto key = parse::readNumberAndMove(line, pos, 2);
    pos++;
    const auto value = parse::readNumberAndMove(line, pos);
    rules[key.value()].push_back(value.value());
}

void readUpdate(std::string_view line, std::vector<std::vector<int>>& numbers) {
    std::vector<int> update;
    size_t pos = 0;
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

void read(std::string_view path, std::map<int, std::vector<int>>& rules, std::vector<std::vector<int>>& numbers) {
    std::ifstream inputFile(path);
    if (!inputFile) {
        std::cerr << "Error opening file " << path << std::endl;
    }

    std::string line;
    bool readingRules = true;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            readingRules = false;
            continue;
        }

        std::stringstream ss(line);

        if (readingRules) {
            readRule(line, rules);
        } else {
            readUpdate(line, numbers);
        }
    }
}

bool checkUpdate(const std::map<int, std::vector<int>>& rules, const std::vector<int>& update) {
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

void fixUpdateOrder(const std::map<int, std::vector<int>>& rules, std::vector<int>& update) {
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
    read("input.txt", rules, numbers);

    int sum = 0;
    for (const auto& update : numbers) {
        if (checkUpdate(rules, update)) {
            sum += getMiddle(update);
        }
    }

    std::cout << "Correct updates sum: " << sum << std::endl;
}

void task2() {
    std::map<int, std::vector<int>> rules;
    std::vector<std::vector<int>> numbers;
    read("input.txt", rules, numbers);

    int sum = 0;
    for (auto& update : numbers) {
        if (!checkUpdate(rules, update)) {
            while (!checkUpdate(rules, update)) {
                fixUpdateOrder(rules, update);
            }
            sum += getMiddle(update);
        }
    }

    std::cout << "Fixed updates sum: " << sum << std::endl;
}

int main() {
    task1(); // 4281
    task2(); // 5466
    return 0;
}
