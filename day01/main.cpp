#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

int task1() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::vector<int> numbers1;
    std::vector<int> numbers2;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        int num1, num2;

        if (ss >> num1 >> num2) {
            numbers1.push_back(num1);
            numbers2.push_back(num2);
        } else {
            std::cerr << "Error reading numbers from line: " << line << std::endl;
        }
    }
    inputFile.close();

    std::sort(numbers1.begin(), numbers1.end());
    std::sort(numbers2.begin(), numbers2.end());

    int sum = 0;
    for (int i = 0; i < numbers1.size(); i++) {
        sum += std::abs(numbers1[i] - numbers2[i]);
    }
    std::cout << "Sum of differences: " << sum << std::endl;
}

int task2() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::vector<int> left;
    std::vector<int> right;

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        int num1, num2;

        if (ss >> num1 >> num2) {
            left.push_back(num1);
            right.push_back(num2);
        } else {
            std::cerr << "Error reading numbers from line: " << line << std::endl;
        }
    }
    inputFile.close();

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
    task1();
    task2();
}
