#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

int main() {
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

    return 0;
}

// clang++ -Wall -std=c++20 -Ilibs/ main.cpp -o build/main.a
