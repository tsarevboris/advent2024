#include <iostream>
#include "common/file.h"
#include "common/parse.h"
#include <map>
#include <vector>
#include <string>

struct TestSet {
    long long test;
    std::vector<long long> values;
};

void readData(std::string_view path, std::vector<TestSet>& data) {
    std::ifstream inputFile(path);
    if (!inputFile) {
        std::cerr << "Error opening file " << path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue;  // Skip empty lines
        }

        std::stringstream ss(line);

        size_t pos = 0;
        const auto test = parse::readLongAndMove(line, pos);
        if (!test) {
            std::cerr << "Error reading number from line " << line << std::endl;
            return;
        }
        parse::checkCharAndMove(line, ':', pos);
        parse::checkCharAndMove(line, ' ', pos);


        TestSet set;
        set.test = *test;
        while (true) {
            const auto number = parse::readLongAndMove(line, pos);
            if (!number) {
                break;
            }
            set.values.push_back(*number);
            parse::checkCharAndMove(line, ' ', pos);
        }
        data.push_back(set);
    }

    size_t i = 1;
    for (const auto& [key, value] : data) {
        std::cout << i << " - " << key << ": ";
        for (const auto& v : value) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
        i++;
    }
}

long long concat(long long a, long long b) {
//    auto startA = a;
//    auto startB = b;

    long long c = b;
    while (c > 0) {
        a *= 10;
        c /= 10;
    }

    //std::cout << startA << " || " << startB << " = " << a + b << std::endl;

    return a + b;
}

bool checkTest(long long test, long long result, size_t pos, std::vector<long long> values, std::string expression) {
    if (pos >= values.size()) {
//        if (test == result) {
//            std::cout << test << " = " << expression << std::endl;
//        }
        return test == result;
    } else {
        return
            checkTest(test, result * values[pos], pos + 1, values, expression + " * " + std::to_string(values[pos])) ||
            checkTest(test, result + values[pos], pos + 1, values, expression + " + " + std::to_string(values[pos]));
    }
}

bool checkTest2(long long test, long long result, size_t pos, std::vector<long long> values, std::string expression) {
    if (pos >= values.size()) {
//        if (test == result) {
//            std::cout << test << " = " << expression << std::endl;
//        }
        return test == result;
    } else {
        return
                checkTest2(test, result * values[pos], pos + 1, values, expression + " * " + std::to_string(values[pos])) ||
                checkTest2(test, result + values[pos], pos + 1, values, expression + " + " + std::to_string(values[pos])) ||
                checkTest2(test, concat(result, values[pos]), pos + 1, values, expression + " || " + std::to_string(values[pos]));
    }
}

bool checkTest(long long test, std::vector<long long> values) {
    std::string expression = std::to_string(values[0]);
    return checkTest(test, values[0], 1, values, expression);
}

bool checkTest2(long long test, std::vector<long long> values) {
    std::string expression = std::to_string(values[0]);
    return checkTest2(test, values[0], 1, values, expression);
}

void task1() {
    std::vector<TestSet> data;
    readData("input.txt", data);

    long long result = 0;
    for (const auto& [test, values] : data) {
        if (checkTest(test, values)) {
            result += test;
            //std::cout << "Sub result: " << result << std::endl;
        }
    }

    std::cout << "Result: " << result << std::endl;
}

void task2() {
    std::vector<TestSet> data;
    readData("input.txt", data);

    long long result = 0;
    for (const auto& [test, values] : data) {
        if (checkTest2(test, values)) {
            result += test;
            //std::cout << "Sub result: " << result << std::endl;
        }
    }

    std::cout << "Result: " << result << std::endl;
}

int main() {
//    task1();
    task2();
    return 0;
}
