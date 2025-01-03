#include <iostream>
#include "common/file.h"
#include <array>
#include <cmath>
#include <set>

std::vector<long long> readData(const std::string& filename) {
    std::vector<long long> data;
    std::ifstream file(filename);
    if (file.is_open()) {
        long long num;
        while (file >> num) {
            data.push_back(num);
        }
    }
    return data;
};

long long mix(long long secret, long long num) {
    return secret ^ num;
}

long long prune(long long secret) {
    return secret % 16777216;
}

long long getNextSecret(long long secret) {
    const auto step1 = prune(mix(secret, secret * 64));
    const auto step2 = prune(mix(step1, std::floor(static_cast<double>(step1) / 32)));
    const auto step3 = prune(mix(step2, step2 * 2048));
    return step3;
}

int getDigitSecret(long long secret) {
    return secret % 10;
}

void task1() {
    auto data = readData("input.txt");
    for (int i = 0; i < 2000; i++) {
        for (long long& num : data) {
            num = getNextSecret(num);
        }
    }

    // calculate sum
    long long sum = 0;
    for (const auto& num : data) {
        sum += num;
    }

    std::cout << "Sum: " << sum << std::endl;
}

std::vector<std::vector<int>> getCombinations() {
    std::vector<std::vector<int>> combinations;

    // value can be from -9 to 9
    // each combination has 4 such values
    for (size_t i = 0; i < 19; i++) {
        for (size_t j = 0; j < 19; j++) {
            for (size_t k = 0; k < 19; k++) {
                for (size_t l = 0; l < 19; l++) {
                    combinations.push_back({static_cast<int>(i) - 9, static_cast<int>(j) - 9, static_cast<int>(k) - 9, static_cast<int>(l) - 9});
                }
            }
        }
    }

    return combinations;
}

void task2() {
    auto data = readData("input.txt");

    std::vector<std::vector<int>> possibleCombinations;
    std::set<int> hashes;

    std::vector<std::vector<long long>> sequences(data.size());
    for (size_t numIndex = 0; numIndex < data.size(); numIndex++) {
        std::vector<long long> sequence(2001);
        std::vector<int> combination;
        sequence[0] = getDigitSecret(data[numIndex]);
        for (int i = 1; i < 2001; i++) {
            data[numIndex] = getNextSecret(data[numIndex]);
            sequence[i] = getDigitSecret(data[numIndex]);
            auto diff = sequence[i] - sequence[i - 1];
            if (combination.size() < 4) {
                combination.push_back(diff);
            } else {
                combination[0] = combination[1];
                combination[1] = combination[2];
                combination[2] = combination[3];
                combination[3] = diff;
            }
            if (combination.size() == 4) {
                const int calcCombHash = combination[0] * 1000 + combination[1] * 100 + combination[2] * 10 + combination[3];
                if (!hashes.contains(calcCombHash)) {
                    hashes.insert(calcCombHash);
                    possibleCombinations.push_back(combination);
                }
            }
        }
        sequences[numIndex] = sequence;
    }

    long long maxPrice = 0;
    int combNum = 0;
    const auto combinations = possibleCombinations;
    for (const auto& comb : combinations) {
        if (combNum % 100 == 0) {
            std::cout << "Combination: " << combNum << "/" << combinations.size() << std::endl;
            std::cout << "Max price: " << maxPrice << std::endl;
        }
        combNum++;

        long long price = 0;

//        int seqNum = 0;
        for (const auto& sequence : sequences) {
//            std::cout << "Sequence: " << seqNum++ << std::endl;

            std::vector<int> seqComb(4);
            seqComb[0] = sequence[1] - sequence[0];
            seqComb[1] = sequence[2] - sequence[1];
            seqComb[2] = sequence[3] - sequence[2];
            seqComb[3] = sequence[4] - sequence[3];

            for (size_t i = 4; i < sequence.size(); i++) {
                if (seqComb == comb) {
                    price += sequence[i];
                    break;
                }

                if (i + 1 < sequence.size()) {
                    // shift seqComb to left
                    seqComb[0] = seqComb[1];
                    seqComb[1] = seqComb[2];
                    seqComb[2] = seqComb[3];
                    seqComb[3] = sequence[i + 1] - sequence[i];
                }
            }
        }

        maxPrice = std::max(maxPrice, price);
    }

    std::cout << "Max price: " << maxPrice << std::endl;
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
