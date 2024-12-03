#include <iostream>
#include <string>
#include <map>
#include "common/file.h"

void task1() {
    auto numbers = file::readAsColumns("input.txt");
    if (numbers.size() != 2) {
        std::cerr << "Invalid input!" << std::endl;
        return;
    }

    auto& numbers1 = numbers[0];
    auto& numbers2 = numbers[1];

    std::ranges::sort(numbers1);
    std::ranges::sort(numbers2);

    int sum = 0;
    for (size_t i = 0; i < numbers1.size(); i++) {
        sum += std::abs(numbers1[i] - numbers2[i]);
    }
    std::cout << "Sum of differences: " << sum << std::endl;
}

void task2() {
    const auto numbers = file::readAsColumns("input.txt");
    if (numbers.size() != 2) {
        std::cerr << "Invalid input!" << std::endl;
        return;
    }

    const auto& left = numbers[0];
    const auto& right = numbers[1];

    std::map<int, int> rightCount;
    for (int num : right) {
        rightCount[num]++;
    }

    int score = 0;
    for (int num : left) {
        score += num * rightCount[num];
    }

    std::cout << "Similarity score: " << score << std::endl;
};

int main() {
    task1(); // 1197984
    task2(); // 23387399
    return 0;
}
