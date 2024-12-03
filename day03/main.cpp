#include <iostream>
#include <optional>
#include "common/file.h"

bool readString(const std::string& input, const std::string& str, size_t& pos) {
    if (input.compare(pos, str.size(), str) == 0) {
        pos += str.size();
        return true;
    }
    return false;
}

bool findString(const std::string& input, const std::string& str, size_t& pos) {
    pos = input.find(str, pos);
    bool result = pos != std::string::npos;
    pos += 4;
    return result;
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

std::optional<int> readNumber(const std::string& input, size_t& pos) {
    int number = 0;
    int maxDigits = 3;
    int i = 0;
    for (; i < maxDigits && pos < input.size() && isDigit(input[pos]); i++) {
        number = number * 10 + (input[pos] - '0');
        pos++;
    }
    return i > 0 ? std::make_optional(number) : std::nullopt;
}

bool readSymbol(const std::string& input, char symbol, size_t& pos) {
    bool found = pos < input.size() && input[pos] == symbol;
    if (found) {
        pos++;
    }
    return found;
}

void task1() {
    const auto input = file::readFileAsString("input.txt");

    int sum = 0;
    size_t pos = 0;
    while (pos < input.size()) {
        // try read operation and opening parenthesis
        if (!findString(input, "mul(", pos)) {
            break;
        }

        // try to read first number
        const auto left = readNumber(input, pos);
        if (!left) {
            continue;
        }

        // try read comma
        if (!readSymbol(input, ',', pos)) {
            continue;
        }

        // try to read second number
        const auto right = readNumber(input, pos);
        if (!right) {
            continue;
        }

        // read closing parenthesis
        if (!readSymbol(input, ')', pos)) {
            continue;
        }

        sum += *left * *right;
    }

    std::cout << "Sum: " << sum << std::endl;
}

void task2() {
    const auto input = file::readFileAsString("input.txt");

    int sum = 0;
    size_t pos = 0;
    bool enabled = true;
    while (pos < input.size()) {
        if (enabled) {
            // Try disable
            const auto exprPos = input.find("mul(", pos);
            if (exprPos == std::string::npos) {
                break;
            }

            const auto disablePos = input.find("don't()", pos);
            if (disablePos != std::string::npos && disablePos < exprPos) {
                enabled = false;
                pos = disablePos + 7;
                continue;
            }
        } else {
            // Try enable
            if (findString(input, "do()", pos)) {
                enabled = true;
            } else {
                break;
            }
        }

        // try read operation and opening parenthesis
        if (!findString(input, "mul(", pos)) {
            break;
        }

        // try to read first number
        const auto left = readNumber(input, pos);
        if (!left) {
            continue;
        }

        // try read comma
        if (!readSymbol(input, ',', pos)) {
            continue;
        }

        // try to read second number
        const auto right = readNumber(input, pos);
        if (!right) {
            continue;
        }

        // read closing parenthesis
        if (!readSymbol(input, ')', pos)) {
            continue;
        }

        sum += *left * *right;
    }

    std::cout << "Sum: " << sum << std::endl;
}

int main() {
    task1();
    task2();
    return 0;
}
