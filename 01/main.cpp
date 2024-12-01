#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main() {
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

    return 0;
}

// clang++ -Wall -std=c++20 -Ilibs/ main.cpp -o build/main.a
