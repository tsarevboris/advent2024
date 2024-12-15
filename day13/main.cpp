#include <iostream>
#include "common/file.h"
#include "common/parse.h"

constexpr int buttonAPrice = 3;
constexpr int buttonBPrice = 1;

struct Button {
    long long x;
    long long y;
};

struct Prize {
    long long x;
    long long y;
};

struct Machine {
    Button buttonA;
    Button buttonB;
    Prize prize;
};

std::vector<Machine> readMachines(std::string_view file) {
    std::ifstream inputFile(file);
    if (!inputFile) {
        std::cerr << "Error opening file " << file << std::endl;
        return {};
    }

    std::vector<Machine> machines;

    while (true) {
        Machine machine;

        std::string buttonALine;
        std::getline(inputFile, buttonALine);
        size_t pos = 12;
        if (auto num = parse::readNumberAndMove(buttonALine, pos)) {
            machine.buttonA.x = *num;
        }
        pos +=4;
        if (auto num = parse::readNumberAndMove(buttonALine, pos)) {
            machine.buttonA.y = *num;
        }

        std::string buttonBLine;
        std::getline(inputFile, buttonBLine);
        pos = 12;
        if (auto num = parse::readNumberAndMove(buttonBLine, pos)) {
            machine.buttonB.x = *num;
        }
        pos +=4;
        if (auto num = parse::readNumberAndMove(buttonBLine, pos)) {
            machine.buttonB.y = *num;
        }

        std::string prizeLine;
        std::getline(inputFile, prizeLine);
        pos = 9;
        if (auto num = parse::readNumberAndMove(prizeLine, pos)) {
            machine.prize.x = *num;
        }
        pos +=4;
        if (auto num = parse::readNumberAndMove(prizeLine, pos)) {
            machine.prize.y = *num;
        }

        machines.push_back(machine);

        std::string emptyLIne;
        if (!std::getline(inputFile, emptyLIne)) {
            break;
        }
    }

    return machines;
}

void calculatePrices(const Machine& machine, long long positionX, long long positionY,
                     long long price, long long& minPrice,
                     std::unordered_map<std::string, long long>& prices) {
    if (machine.prize.x == positionX && machine.prize.y == positionY) {
        minPrice = std::min(minPrice, price);
    } else if (positionX > machine.prize.x || positionY > machine.prize.y) {
        return;
    } else if (price >= minPrice) {
        return;
    }

    const auto positionKey = std::to_string(positionX) + "_" + std::to_string(positionY);
    if (prices.contains(positionKey) && prices[positionKey] <= price) {
        return;
    }

    prices[positionKey] = price;
    calculatePrices(machine, positionX + machine.buttonA.x, positionY + machine.buttonA.y, price + buttonAPrice, minPrice, prices);
    calculatePrices(machine, positionX + machine.buttonB.x, positionY + machine.buttonB.y, price + buttonBPrice, minPrice, prices);
}

long long calculatePrice(const Machine& machine) {
    long long minPrice = std::numeric_limits<long long>::max();
    std::unordered_map<std::string, long long> prices;
    calculatePrices(machine, 0, 0, 0, minPrice, prices);
    return minPrice;
}

long long calculatePrice2(const Machine& machine) {
    long long minPrice = std::numeric_limits<long long>::max();

    // Maximum value for `a` such that `a * buttonA.x <= prize.x` and `a * buttonA.y <= prize.y`
    long long maxA = std::min(machine.prize.x / machine.buttonA.x, machine.prize.y / machine.buttonA.y);

    for (long long a = 0; a <= maxA; ++a) {
        long long remainingX = machine.prize.x - a * machine.buttonA.x;
        long long remainingY = machine.prize.y - a * machine.buttonA.y;

        // Check if remainingX and remainingY can be achieved with button B presses
        if (remainingX % machine.buttonB.x == 0 && remainingY % machine.buttonB.y == 0) {
            long long bX = remainingX / machine.buttonB.x;
            long long bY = remainingY / machine.buttonB.y;

            // Ensure the same `b` applies to both directions
            if (bX == bY && bX >= 0) {
                long long price = a * buttonAPrice + bX * buttonBPrice;
                minPrice = std::min(minPrice, price);
            }
        }
    }

    return minPrice == std::numeric_limits<long long>::max() ? -1 : minPrice;
}

long long calculatePrice3(const Machine& machine) {
    auto A = static_cast<double>(machine.prize.x * machine.buttonB.y - machine.prize.y * machine.buttonB.x) /
               (machine.buttonA.x * machine.buttonB.y - machine.buttonA.y * machine.buttonB.x);
    if (A < 0 || A != std::floor(A)) {
        return -1;
    }

    auto B = static_cast<double>(machine.prize.x - machine.buttonA.x * A) / machine.buttonB.x;
    if (B < 0 || B != std::floor(B)) {
        return -1;
    }

    return static_cast<long long>(A * buttonAPrice + B * buttonBPrice);
}

void task1() {
    const auto machines = readMachines("input.txt");

    long long sum = 0;
    for (const auto& machine : machines) {
        const auto price = calculatePrice3(machine);
        if (price > 0) {
            sum += price;
        }
    }

    std::cout << "Total price: " << sum << std::endl;
}

void task2() {
    auto machines = readMachines("input.txt");
    for (auto& machine : machines) {
        machine.prize.x += 10000000000000;
        machine.prize.y += 10000000000000;
    }

    long long sum = 0;
    for (const auto& machine : machines) {
        const auto price = calculatePrice3(machine);
        if (price >= 0) {
            sum += price;
        }
    }

    std::cout << "Total price: " << sum << std::endl;
}



int main() {
    std::cout << "Task 1: " << std::endl;
    task1(); // 29598
    std::cout << "-----------" << std::endl;

    std::cout << "Task 2: " << std::endl;
    task2(); // 93217456941970
    std::cout << "-----------" << std::endl;
    return 0;

    return 0;
}
