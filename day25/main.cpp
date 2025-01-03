#include <iostream>
#include "common/file.h"

struct Lock {
    Lock() {
        values.fill(0);
    }
    std::array<int, 5> values;
};

struct Key {
    Key() {
        values.fill(0);
    }
    std::array<int, 5> values;
};

void readData(std::vector<Lock>& locks, std::vector<Key>& keys) {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file input.txt" << std::endl;
        return;
    }

    std::string line;
    bool isLock = false;
    bool isKey = false;
    Lock lock;
    Key key;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            if (isLock) {
                locks.push_back(lock);
                lock = Lock();
                isLock = false;
            }

            if (isKey) {
                keys.push_back(key);
                key = Key();
                isKey = false;
            }
            continue;
        }

        if (!isLock && !isKey) {
            isLock = line[0] == '#';
            isKey = line[0] == '.';
            continue;
        }

        if (isLock) {
            for (size_t i = 0; i < 5; ++i) {
                lock.values[i] += (line[i] == '#' ? 1 : 0);
            }
        }

        if (isKey) {
            for (size_t i = 0; i < 5; ++i) {
                key.values[i] += (line[i] == '#' ? 1 : 0);
            }
        }
    }

    if (isLock) {
        locks.push_back(lock);
    }

    if (isKey) {
        keys.push_back(key);
    }

    // substruct 1 from each key value
    for (auto& keyV : keys) {
        for (size_t i = 0; i < 5; ++i) {
            keyV.values[i] -= 1;
        }
    }
}

void task1() {
    std::vector<Lock> locks;
    std::vector<Key> keys;
    readData(locks, keys);

    std::cout << "Locks: " << std::endl;
    for (const auto& lock : locks) {
        for (size_t i = 0; i < 5; ++i) {
            std::cout << lock.values[i] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Keys: " << std::endl;
    for (const auto& key : keys) {
        for (size_t i = 0; i < 5; ++i) {
            std::cout << key.values[i] << " ";
        }
        std::cout << std::endl;
    }
}

void task2() {
    std::vector<Lock> locks;
    std::vector<Key> keys;
    readData(locks, keys);

    int matchCount = 0;
    for (const Lock& lock : locks) {
        for (const Key& key : keys) {
            bool isMatch = true;
            for (size_t i = 0; i < 5; ++i) {
                if (lock.values[i] + key.values[i] > 5) {
                    isMatch = false;
                    break;
                }
            }

            if (isMatch) {
                matchCount++;
            }
        }
    }

    std::cout << "Match count: " << matchCount << std::endl;
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
