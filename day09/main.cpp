#include <iostream>
#include "common/file.h"
#include <vector>

void task1() {
    const auto data = file::readNumbers("input.txt");
    std::cout << "\nData:\n";
    for (const auto& num : data) {
        std::cout << num;
    }

    std::vector<int> expandedData;
    int group = 0;
    for (size_t i = 0; i < data.size(); i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < data[i]; j++) {
                expandedData.push_back(group);
            }
            group++;
        } else {
            for (int j = 0; j < data[i]; j++) {
                expandedData.push_back(-1);
            }
        }
    }

    std::cout << "\nExpanded data:\n";
    for (const auto& num : expandedData) {
        std::cout << num << ' ';
    }

    // Compress
    size_t front = 0;
    size_t back = expandedData.size() - 1;
    while (front < back) {
        if (expandedData[front] != -1) {
            front++;
            continue;
        }

        while (expandedData[back] == -1) {
            back--;
        }

        if (front < back) {
            std::swap(expandedData[front], expandedData[back]);
        }
    }

    std::cout << "\nCompressed data:\n";
    for (const auto& num : expandedData) {
        std::cout << num;
    }

    // Checksum
    long long sum = 0;
    for (size_t i = 0; i < expandedData.size(); i++) {
        if (expandedData[i] == -1) {
            continue;
        }
        sum += i * expandedData[i];
    }

    std::cout << "\nChecksum: " << sum << '\n';
}

std::vector<int> getDigits(int num) {
    std::vector<int> digits;
    while (num > 0) {
        digits.push_back(num % 10);
        num /= 10;
    }

    //reverse
    std::reverse(digits.begin(), digits.end());
    return digits;
}

void task2() {
    const auto data = file::readNumbers("input.txt");
    std::cout << "\nData:\n";
    for (const auto& num : data) {
        std::cout << num;
    }

    std::vector<int> expandedData;
    int group = 0;
    for (size_t i = 0; i < data.size(); i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < data[i]; j++) {
                expandedData.push_back(group);
            }
            group++;
        } else {
            for (int j = 0; j < data[i]; j++) {
                expandedData.push_back(-1);
            }
        }
    }

    std::cout << "\nExpanded data:\n";
    for (const auto& num : expandedData) {
        if (num == -1) {
            std::cout << "*";
        } else if (num == -2) {
            std::cout << "_";
        } else {
            std::cout << num;
        }
    }

    // Compress
    int front = 0;
    int back = expandedData.size() - 1;
    for (size_t test = 0; test < 1; test++) {
        std::cout<< "\n" << "step" << test << "\n";
        while (back > 0) {
            auto backValue = expandedData[back];
            while (backValue < 0 && back > 0) {
                back--;
                backValue = expandedData[back];
            }
            size_t backSize = 0;
            while (expandedData[back] == backValue && back > 0) {
                backSize++;
                back--;
            }
            back++;

            front = 0;
            int blockStart = 0;
            while (front < back) {
                auto frontValue = expandedData[front];
                while (frontValue != -1 && front < back) {
                    front++;
                    frontValue = expandedData[front];
                }

                blockStart = front;
                size_t emptySize = 0;
                while (expandedData[front] == -1 && front < back) {
                    emptySize++;
                    front++;
                }

                if (blockStart < back && emptySize >= backSize) {
                    for (size_t i = 0; i < backSize; i++) {
                        std::swap(expandedData[blockStart + i], expandedData[back + i]);
                    }
                    break;
                }
            }
            back--;

//            std::cout << "\nCompressed data step:\n";
//            for (const auto& num : expandedData) {
//                if (num == -1) {
//                    std::cout << "*";
//                } else if (num == -2) {
//                    std::cout << "_";
//                } else {
//                    std::cout << num;
//                }
//            }
        }
        back = expandedData.size() - 1;
    }

    std::cout << "\nCompressed data:\n";
    for (const auto& num : expandedData) {
        std::cout << num;
    }

    // Checksum
    long long sum = 0;
    long long groupNum = 0;
    for (size_t i = 0; i < expandedData.size(); i++) {
        if (expandedData[i] == -2) {
            continue;
        }

        if (expandedData[i] == -1) {
            groupNum++;
            continue;
        }

        sum += groupNum * expandedData[i];
        groupNum++;
    }

    std::cout << "\nChecksum: " << sum << '\n';
}

int main() {
//    task1();
    task2();
    return 0;
}
