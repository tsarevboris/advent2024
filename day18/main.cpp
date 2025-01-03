#include <iostream>
#include "common/file.h"
#include "common/parse.h"
#include <vector>
#include <string>

struct Cell {
    int x;
    int y;
};

const auto dirs = std::vector<TableStep>{
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};

constexpr int tableSize = 71;
constexpr int simSteps = 1024;

void find(Table<char>& table, Table<int>& lens, Cell cell, int len, int& minLen) {
    if (cell.x == tableSize - 1 && cell.y == tableSize - 1) {
        minLen = std::min(minLen, len);
        return;
    }

    if (len >= lens(cell.y, cell.x)) {
        return;
    }
    lens(cell.y, cell.x) = len;

    for (const auto& dir : dirs) {
        const auto newX = cell.x + dir.rowDiff;
        const auto newY = cell.y + dir.columnDiff;

        if (newX < 0 ||  newX >= tableSize || newY < 0 || newY >= tableSize) {
            continue;
        }

        if (table(newY, newX) == '#') {
            continue;
        }

        if (table(newY, newX) == '.') {
            find(table, lens, {newX, newY}, len + 1, minLen);
        }
    }

}

void task1() {
    std::ifstream inputFile("input.txt");

    std::vector<Cell> bytes;
    std::string line;
    while (std::getline(inputFile, line)) {
        size_t pos = 0;
        const auto x = parse::readNumberAndMove(line, pos).value();
        pos += 1;
        const auto y = parse::readNumberAndMove(line, pos).value();

        bytes.push_back({x, y});
    }

    Table table(tableSize, tableSize, '.');

    // simulate
    for (auto i = 0; i < simSteps; i++) {
        table[bytes[i].y][bytes[i].x] = '#';
    }

    int minLen = INT_MAX;
    Table lens(tableSize, tableSize, INT_MAX);
    find(table, lens, {0, 0}, 0, minLen);

    // print min len
    std::cout << "Min len: " << minLen << std::endl;
}

void task2() {
    std::ifstream inputFile("input.txt");

    std::vector<Cell> bytes;
    std::string line;
    while (std::getline(inputFile, line)) {
        size_t pos = 0;
        const auto x = parse::readNumberAndMove(line, pos).value();
        pos += 1;
        const auto y = parse::readNumberAndMove(line, pos).value();

        bytes.push_back({x, y});
    }

    Table table(tableSize, tableSize, '.');

    // simulate
    for (size_t i = 0; i < bytes.size(); i++) {
        table[bytes[i].y][bytes[i].x] = '#';

        if (i >= 3000) {
            std::cout << "Byte " << i << std::endl;
            int minLen = INT_MAX;
            Table lens(tableSize, tableSize, INT_MAX);
            find(table, lens, {0, 0}, 0, minLen);

            if (minLen == INT_MAX) {
                std::cout << "Byte " << bytes[i].x << "," << bytes[i].y << " blocks the way" << std::endl;
                break;
            }
        }
    }
}

int main() {
    std::cout << "Task 1: " << std::endl;
    task1(); // 370
    std::cout << "-----------" << std::endl;

    std::cout << "Task 2: " << std::endl;
    task2(); // 65,6
    std::cout << "-----------" << std::endl;
    return 0;
}
