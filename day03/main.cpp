#include <iostream>
#include "common/file.h"
#include "common/parse.h"

void task1() {
    const auto input = file::readString("input.txt");

    int sum = 0;
    size_t pos = 0;
    while (pos < input.size()) {
        // Operation and opening parenthesis
        if (!parse::findStringAndMove(input, "mul(", pos)) {
            break;
        }

        // First number
        const auto left = parse::readNumberAndMove(input, pos);
        if (!left) {
            continue;
        }

        // Comma
        if (!parse::checkCharAndMove(input, ',', pos)) {
            continue;
        }

        // Second number
        const auto right = parse::readNumberAndMove(input, pos);
        if (!right) {
            continue;
        }

        // Closing parenthesis
        if (!parse::checkCharAndMove(input, ')', pos)) {
            continue;
        }

        sum += *left * *right;
    }

    std::cout << "Sum: " << sum << std::endl;
}

void task2() {
    const auto input = file::readString("input.txt");

    int sum = 0;
    size_t pos = 0;
    bool enabled = true;
    while (pos < input.size()) {
        if (enabled) {
            // Disable summation if "don't()" is found before "mul("
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
            // Enable summation again
            if (parse::findStringAndMove(input, "do()", pos)) {
                enabled = true;
            } else {
                break;
            }
        }

        // Operation and opening parenthesis
        if (!parse::findStringAndMove(input, "mul(", pos)) {
            break;
        }

        // First number
        const auto left = parse::readNumberAndMove(input, pos);
        if (!left) {
            continue;
        }

        // Comma
        if (!parse::checkCharAndMove(input, ',', pos)) {
            continue;
        }

        // Second number
        const auto right = parse::readNumberAndMove(input, pos);
        if (!right) {
            continue;
        }

        // Closing parenthesis
        if (!parse::checkCharAndMove(input, ')', pos)) {
            continue;
        }

        sum += *left * *right;
    }

    std::cout << "Sum: " << sum << std::endl;
}

int main() {
    task1(); // 171183089
    task2(); // 63866497
    return 0;
}
