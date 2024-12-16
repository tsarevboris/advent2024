#include <iostream>
#include "common/file.h"
#include <queue>
#include <map>
#include <unordered_map>

struct Cell {
    int row;
    int column;

    bool operator==(const Cell& other) const = default;
};

const std::vector<TableStep> steps = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}
};

void search(Table<char>& table, Cell cell, TableStep dir, int sum, Table<int>& sums) {
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
        const auto nextCell = Cell{cell.row + step.rowDiff, cell.column + step.columnDiff};
        if (nextCell.row < 0 || nextCell.row >= static_cast<int>(table.rowCount()) ||
            nextCell.column < 0 || nextCell.column >= static_cast<int>(table.columnCount())) {
            continue;
        }
        if (table(nextCell.row, nextCell.column) == '#') {
            continue;
        }
        if (step == dir) {
            search(table, nextCell, dir, sum + 1, sums);
        } else {
            search(table, nextCell, step, sum + 1001, sums);
        }
    }
}

void task1() {
    auto table = file::readTable<char>("input.txt");
    Table<int> sums{table.rowCount(), table.columnCount(), INT_MAX};
    Cell start{static_cast<int>(table.rowCount()) - 2, 1};
    TableStep dir{0, 1};

    search(table, start, dir, 0, sums);

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

    const auto end = sums(1, static_cast<int>(table.columnCount()) - 2);
    std::cout << "Shortest path: " << end << std::endl;
}

struct Pos {
    int row;
    int column;
    int sum;
    int dirX;
    int dirY;

    std::vector<Cell> path;
};

struct Sum {
    std::map<TableStep, int> values = {
        {{0, 1}, INT_MAX},
        {{1, 0}, INT_MAX},
        {{0, -1}, INT_MAX},
        {{-1, 0}, INT_MAX}
    };

    int min() {
        return std::min({values[{0, 1}], values[{1, 0}], values[{0, -1}], values[{-1, 0}]});
    }
};

void search2(Table<char>& table, std::queue<Pos>& poses, Table<Sum>& sums, Table<int>& seats) {
    while (!poses.empty()) {
        const auto posesSize = poses.size();
        for (size_t i = 0; i < posesSize; i++) {
            auto pos = poses.front();
            poses.pop();

            TableStep posStep = {pos.dirX, pos.dirY};
            if (pos.sum > sums(pos.row, pos.column).values[posStep]) {
                continue;
            }
            sums(pos.row, pos.column).values[posStep] = pos.sum;

            if (table(pos.row, pos.column) == 'E') {
                // Found the end
                // Mark seats using path
                for (const auto& cell : pos.path) {
                    seats(cell.row, cell.column) = std::min(seats(cell.row, cell.column), pos.sum);
                }
                continue;
            }

            for (const auto &step: steps) {
                if (step.rowDiff + pos.dirX == 0 && step.columnDiff + pos.dirY == 0) {
                    continue;
                }

                auto nextPos = pos;
                nextPos.row += step.rowDiff;
                nextPos.column += step.columnDiff;

                if (nextPos.row < 0 || nextPos.row >= static_cast<int>(table.rowCount()) ||
                    nextPos.column < 0 || nextPos.column >= static_cast<int>(table.columnCount())) {
                    continue;
                }
                if (table(nextPos.row, nextPos.column) == '#') {
                    continue;
                }

                auto pathCopy = pos.path;
                pathCopy.push_back({nextPos.row, nextPos.column});
                if (step == TableStep{pos.dirX, pos.dirY}) {
                    poses.push({nextPos.row, nextPos.column, pos.sum + 1, step.rowDiff, step.columnDiff, pathCopy});
                } else {
                    poses.push({nextPos.row, nextPos.column, pos.sum + 1001, step.rowDiff, step.columnDiff, pathCopy});
                }
            }
        }
    }
}

void task2() {
    auto table = file::readTable<char>("input.txt");
    Table<Sum> sums{table.rowCount(), table.columnCount()};
    Cell start{static_cast<int>(table.rowCount()) - 2, 1};

    std::vector<Cell> path;
    path.push_back(start);

    Pos pos{start.row, start.column, 0, 0, 1, path};
    std::queue<Pos> poses;
    poses.push(pos);

    Table<int> seats{table.rowCount(), table.columnCount(), INT_MAX};
    search2(table, poses, sums, seats);

    const auto shortestPath = sums(1, static_cast<int>(table.columnCount()) - 2).min();
    std::cout << "Shortest path: " << shortestPath << std::endl;

    // Print sums table with each number taking 4 characters
    for (size_t i = 0; i < sums.rowCount(); i++) {
        for (size_t j = 0; j < sums.columnCount(); j++) {
            if (sums(i, j).min() == INT_MAX) {
                std::cout << "  #   ";
            } else {
                std::cout << " " << std::setw(4) << sums(i, j).min() << " ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    // Print seats count
    // Print sums table with each number taking 4 characters
    int count = 0;
    for (size_t i = 0; i < seats.rowCount(); i++) {
        for (size_t j = 0; j < seats.columnCount(); j++) {
            if (seats(i, j) == INT_MAX) {
                std::cout << "  #   ";
            } else if (seats(i, j) != shortestPath) {
                std::cout << " " << std::setw(4) << seats(i, j) << " ";
            } else {
                std::cout << " " << std::setw(4) << seats(i, j) << " ";
                count++;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Seats count: " << count << std::endl;
}

int main() {
    task1(); // 99460
    task2(); // 500
    return 0;
}
