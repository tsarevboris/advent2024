#include <iostream>
#include "common/file.h"
#include "common/parse.h"

long long A = 0;
long long B = 0;
long long C = 0;

int getComboOperand(int value) {
    if (0 <= value && value <= 3) {
        return value;
    } else if (value == 4) {
        return A;
    } else if (value == 5) {
        return B;
    } else if (value == 6) {
        return C;
    } else {
        std::cerr << "Invalid combo operand: " << value << std::endl;
        return 0;
    }
}

void adv(int value) {
    const auto comboOperand = getComboOperand(value);
    A >>= comboOperand;
}

void bxl(int value) {
    B ^= value;
}

void bst(int value) {
    const auto comboOperand = getComboOperand(value);
    B = comboOperand % 8;
}

int jnz(int value) {
    if (A == 0) {
        return -1;
    }

    return value;
}

void bxc(int) {
    B ^= C;
}

int out(int value) {
    const auto comboOperand = getComboOperand(value);
    return comboOperand % 8;
}

void bdv(int value) {
    const auto comboOperand = getComboOperand(value);
    B >>= comboOperand;
}

void cdv(int value) {
    const auto comboOperand = getComboOperand(value);
    C >>= comboOperand;
}

void execute(const std::vector<int>& program) {
    size_t index = 0;
    while (index < program.size() - 1) {
        const int opcode = program[index];
        const int operand = program[index + 1];
        switch (opcode) {
            case 0:
                adv(operand);
                index += 2;
                break;
            case 1:
                bxl(operand);
                index += 2;
                break;
            case 2:
                bst(operand);
                index += 2;
                break;
            case 3:
                if (jnz(operand) >= 0) {
                    index = jnz(operand);
                } else {
                    index += 2;
                }
                break;
            case 4:
                bxc(operand);
                index += 2;
                break;
            case 5:
                out(operand);
                index += 2;
                break;
            case 6:
                bdv(operand);
                index += 2;
                break;
            case 7:
                cdv(operand);
                index += 2;
                break;
            default:
                std::cerr << "Invalid operation: " << opcode << std::endl;
        }
    }
}

void task1() {
    std::vector<int> program;

    const auto input = file::readString("input.txt");
    size_t pos = 12;
    A = parse::readNumberAndMove(input, pos).value();
    pos += 13;
    B = parse::readNumberAndMove(input, pos).value();
    pos += 13;
    C = parse::readNumberAndMove(input, pos).value();

    pos += 11;
    while (auto num = parse::readNumberAndMove(input, pos)) {
        program.push_back(num.value());
        pos += 1;
    }

    // print values
    std::cout << "A: " << A << std::endl;
    std::cout << "B: " << B << std::endl;
    std::cout << "C: " << C << std::endl;
    // print program
    std::cout << "Program: ";
    for (const auto& num : program) {
        std::cout << num << ",";
    }
    std::cout << std::endl;

    std::cout << "Output: ";
    execute(program);
}

bool executeAndCheck(const std::vector<long long>& program) {
    size_t outputIndex = 0;
    std::vector<int> output;

    size_t index = 0;
    while (index < program.size() - 1 && outputIndex < program.size()) {
        const int opcode = program[index];
        const int operand = program[index + 1];
        switch (opcode) {
            case 0:
                adv(operand);
                index += 2;
                break;
            case 1:
                bxl(operand);
                index += 2;
                break;
            case 2:
                bst(operand);
                index += 2;
                break;
            case 3:
                if (jnz(operand) >= 0) {
                    index = jnz(operand);
                } else {
                    index += 2;
                }
                break;
            case 4:
                bxc(operand);
                index += 2;
                break;
            case 5:
            {
                auto res = out(operand);
                index += 2;
                if (res != program[outputIndex]) {
                    return false;
                }
                outputIndex++;
                break;
            }
            case 6:
                bdv(operand);
                index += 2;
                break;
            case 7:
                cdv(operand);
                index += 2;
                break;
            default:
                std::cerr << "Invalid operation: " << opcode << std::endl;
        }
    }
    return outputIndex == program.size();
}

void task2() {
    std::vector<long long> program;

    const auto input = file::readString("input.txt");
    size_t pos = 12;
    A = parse::readNumberAndMove(input, pos).value();
    pos += 13;
    B = parse::readNumberAndMove(input, pos).value();
    pos += 13;
    C = parse::readNumberAndMove(input, pos).value();

    pos += 11;
    while (auto num = parse::readNumberAndMove(input, pos)) {
        program.push_back(num.value());
        pos += 1;
    }

    long long tryValue = 0;
    while (true) {
        tryValue++;
        A = tryValue;

        if (executeAndCheck(program)) {
            break;
        }
    }

    std::cout << "Try value: " << tryValue << std::endl;
}

int main() {
    std::cout << "Task 1: " << std::endl;
    task1();
    std::cout << "-----------" << std::endl;

    std::cout << "Task 2: " << std::endl;
    task2();
    std::cout << "-----------" << std::endl;
    return 0;
}

