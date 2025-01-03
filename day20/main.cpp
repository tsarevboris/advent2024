#include <iostream>
#include "common/file.h"
#include <map>
#include <optional>
#include <list>
#include <vector>

struct Cell {
    int row;
    int column;
    int sum;

    bool operator==(const Cell& other) const = default;
};

const std::vector<TableStep> steps = {
        {0, 1},
        {1, 0},
        {0, -1},
        {-1, 0}
};

//constexpr int pathWithoutCheats = 84;

void search(Table<char>& table, Cell cell, int sum, Table<int>& sums, int cheatCount) {
    if (sum < sums(cell.row, cell.column)) {
        sums(cell.row, cell.column) = sum;
    } else {
        return;
    }

    if (table(cell.row, cell.column) == 'E') {
        // Found the end
        return;
    }

    for (const auto& step : steps) {
        const auto nextCell = Cell{cell.row + step.rowDiff, cell.column + step.columnDiff, 0};
        if (nextCell.row < 0 || nextCell.row >= static_cast<int>(table.rowCount()) ||
            nextCell.column < 0 || nextCell.column >= static_cast<int>(table.columnCount())) {
            continue;
        }

        if (cheatCount == 1) {
            if (table(nextCell.row, nextCell.column) != '2' && table(nextCell.row, nextCell.column) != 'E') {
                continue;
            }
        }

        if (table(nextCell.row, nextCell.column) == '#') {
            continue;
        } else if (table(nextCell.row, nextCell.column) == '2') {
            if (cheatCount == 1) {
                search(table, nextCell, sum + 1, sums, cheatCount + 1);
            }
        } else if (table(nextCell.row, nextCell.column) == '1') {
            search(table, nextCell, sum + 1, sums, cheatCount + 1);
        } else {
            search(table, nextCell, sum + 1, sums, cheatCount);
        }
    }
}

void task1() {
    auto table = file::readTable<char>("input.txt");
    Table<int> sums{table.rowCount(), table.columnCount(), INT_MAX};

    // Find start cell
    Cell start{-1, -1, 0};
    for (size_t i = 0; i < table.rowCount(); i++) {
        for (size_t j = 0; j < table.columnCount(); j++) {
            if (table(i, j) == 'S') {
                start = Cell{static_cast<int>(i), static_cast<int>(j), 0};
                break;
            }
        }
        if (start.row != -1) {
            break;
        }
    }


    search(table, start, 0, sums, 0);

    // Print sums table with each number taking 4 characters
    for (size_t i = 0; i < sums.rowCount(); i++) {
        for (size_t j = 0; j < sums.columnCount(); j++) {
            if (sums(i, j) == INT_MAX) {
                std::cout << "  #   ";
            } else {
                std::cout << " " << std::setw(4) << sums(i, j) << " ";
            }
        }
        std::cout << std::endl;
    }

    // Find end cell
    Cell endCell{-1, -1, 0};
    for (size_t i = 0; i < table.rowCount(); i++) {
        for (size_t j = 0; j < table.columnCount(); j++) {
            if (table(i, j) == 'E') {
                endCell = Cell{static_cast<int>(i), static_cast<int>(j), 0};
                break;
            }
        }
        if (endCell.row != -1) {
            break;
        }
    }

    const auto shortestPath = sums(endCell.row, endCell.column);
    std::cout << "Shortest path: " << shortestPath << std::endl;

    int bestCount = 0;
    // Place cheat in different places
    for (size_t i = 0; i < table.rowCount(); i++) {
        for (size_t j = 0; j < table.columnCount(); j++) {
            if (table(i, j) == '#') {
                auto tableCopy = table;
                tableCopy(i, j) = '1';
                for (const auto& step : steps) {
                    const auto nextCell = Cell{static_cast<int>(i) + step.rowDiff, static_cast<int>(j) + step.columnDiff, 0};
                    if (nextCell.row < 0 || nextCell.row >= static_cast<int>(table.rowCount()) ||
                        nextCell.column < 0 || nextCell.column >= static_cast<int>(table.columnCount())) {
                        continue;
                    }
                    if (tableCopy(nextCell.row, nextCell.column) == 'S' || tableCopy(nextCell.row, nextCell.column) == '#') {
                        continue;
                    } else {
                        auto tableCopy2 = tableCopy;
                        if (tableCopy(nextCell.row, nextCell.column) != 'E') {
                            tableCopy2(nextCell.row, nextCell.column) = '2';
                        }
                        sums = {table.rowCount(), table.columnCount(), INT_MAX};
                        search(tableCopy2, start, 0, sums, 0);
                        const auto len = sums(endCell.row, endCell.column);
                        if (len != INT_MAX) {
                            const auto saved = shortestPath - len;
                            if (saved >= 100) {
                                bestCount++;
//                                std::cout << "Cheat at (" << i << ", " << j << ") saves " << saved << " steps" << std::endl;
                                // Print table with cheat
//                                for (size_t x = 0; x < tableCopy2.rowCount(); x++) {
//                                    for (size_t y = 0; y < tableCopy2.columnCount(); y++) {
//                                        std::cout << " " << tableCopy2(x, y) << " ";
//                                    }
//                                    std::cout << std::endl;
//                                }
                            }
                        }
                    }
                }
            }
        }
    }

    std::cout << "Best count: " << bestCount << std::endl;
}

//constexpr auto maxCheatCount = 2;

void search2(Table<char>& table, std::queue<Cell>& cells, Table<int>& sums) {
    while (!cells.empty()) {
        const auto cellsCount = cells.size();
        for (size_t i = 0; i < cellsCount; i++) {
            const auto cell = cells.front();
            cells.pop();

            if (sums(cell.row, cell.column) != INT_MAX) {
                continue;
            }
            sums(cell.row, cell.column) = cell.sum;

            if (table(cell.row, cell.column) == 'E') {
                // Found the end
                continue;
            }

            for (const auto& step : steps) {
                const auto nextCell = Cell{cell.row + step.rowDiff, cell.column + step.columnDiff, cell.sum + 1};
                if (nextCell.row < 0 || nextCell.row >= static_cast<int>(table.rowCount()) ||
                    nextCell.column < 0 || nextCell.column >= static_cast<int>(table.columnCount())) {
                    continue;
                }

                if (table(nextCell.row, nextCell.column) == '#') {
                    continue;
                }

                cells.push(nextCell);
            }
        }
    }
}

struct SumsStorage {
    std::list<Table<int>> values;
};

constexpr int maxCheatsCount = 2;

void search3(Table<char>& table, Cell cell, int sum, SumsStorage& storage, Table<int>& sums, int cheatsCount = 0) {
    if (sum < sums(cell.row, cell.column)) {
        sums(cell.row, cell.column) = sum;
    } else {
        return;
    }

    if (table(cell.row, cell.column) == 'E') {
        // Found the end
        return;
    }

    for (const auto& step : steps) {
        const auto nextCell = Cell{cell.row + step.rowDiff, cell.column + step.columnDiff, 0};
        if (nextCell.row < 0 || nextCell.row >= static_cast<int>(table.rowCount()) ||
            nextCell.column < 0 || nextCell.column >= static_cast<int>(table.columnCount())) {
            continue;
        }

        if (cheatsCount > 0 && cheatsCount < maxCheatsCount - 1) {
            search3(table, nextCell, sum + 1, storage, sums, cheatsCount + 1);
            continue;
        }

        if (table(nextCell.row, nextCell.column) == '#') {
            if (cheatsCount == 0) {
                auto newSums = storage.values.back();
                storage.values.push_back(newSums);
                search3(table, nextCell, sum + 1, storage, storage.values.back(), 1);
            }
        } else {
            search3(table, nextCell, sum + 1, storage, sums, cheatsCount);
        }
    }
}

void task2() {
    auto table = file::readTable<char>("input.txt");
    Table<int> sums{table.rowCount(), table.columnCount(), INT_MAX};

    // Find start cell
    Cell start{-1, -1, 0};
    for (size_t i = 0; i < table.rowCount(); i++) {
        for (size_t j = 0; j < table.columnCount(); j++) {
            if (table(i, j) == 'S') {
                start = Cell{static_cast<int>(i), static_cast<int>(j), 0};
                break;
            }
        }
        if (start.row != -1) {
            break;
        }
    }


//    std::queue<Cell> cells;
//    cells.push(start);
    SumsStorage storage;
    storage.values.push_back(sums);
    search3(table, start, 0, storage, storage.values.back());

    // Print sums table with each number taking 4 characters
    for (size_t i = 0; i < storage.values.back().rowCount(); i++) {
        for (size_t j = 0; j < storage.values.back().columnCount(); j++) {
            if (storage.values.back()(i, j) == INT_MAX) {
                std::cout << "  #   ";
            } else {
                std::cout << " " << std::setw(4) << storage.values.back()(i, j) << " ";
            }
        }
        std::cout << std::endl;
    }

    // Find end cell
    Cell endCell{-1, -1, 0};
    for (size_t i = 0; i < table.rowCount(); i++) {
        for (size_t j = 0; j < table.columnCount(); j++) {
            if (table(i, j) == 'E') {
                endCell = Cell{static_cast<int>(i), static_cast<int>(j), 0};
                break;
            }
        }
        if (endCell.row != -1) {
            break;
        }
    }

    for (const auto& pathSums : storage.values) {
        const auto shortestPath = pathSums(endCell.row, endCell.column);
        std::cout << "Shortest path: " << shortestPath << std::endl;
    }
}

int main() {
    std::cout << "Task 1: " << std::endl;
    // task1(); // 9456 - 1502
    std::cout << "-----------" << std::endl;

    std::cout << "Task 2: " << std::endl;
    task2();
    std::cout << "-----------" << std::endl;
    return 0;
}
