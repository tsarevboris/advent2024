#include <iostream>
#include <vector>
#include "common/file.h"
#include "common/parse.h"
#include <queue>

void determineRegion(TableRegion<char>& region, const Table<char>& table, Table<bool>& visited, std::queue<TableCell>& lookupCells) {
    while (!lookupCells.empty()) {
        const auto cell = lookupCells.front();
        lookupCells.pop();
        if (visited(cell.row, cell.column)) {
            continue;
        }
        visited.set(cell.row, cell.column, true);
        region.cells.push_back({cell.row, cell.column});

        static std::vector<TableStep> steps = {
            {1, 0},
            {-1, 0},
            {0, 1},
            {0, -1}
        };

        for (const auto& step : steps) {
            const auto nextRow = static_cast<int>(cell.row) + step.rowDiff;
            const auto nextColumn = static_cast<int>(cell.column) + step.columnDiff;
            if (nextRow < 0 || nextRow >= static_cast<int>(table.rowCount())) {
                region.perimeter++;
                continue;
            }
            if (nextColumn < 0 || nextColumn >= static_cast<int>(table.columnCount())) {
                region.perimeter++;
                continue;
            }
            if (table(nextRow, nextColumn) != region.value) {
                region.perimeter++;
                continue;
            }

            if (!visited(nextRow, nextColumn)) {
                lookupCells.push({static_cast<size_t>(nextRow), static_cast<size_t>(nextColumn)});
            }
        }

        static std::vector<std::pair<TableStep, TableStep>> cornerSteps = {
                {
                        {0, -1},
                        {-1, 0}
                },
                {
                        {-1, 0},
                        {0, 1}
                },
                {
                        {0, 1},
                        {1, 0}
                },
                {
                        {1, 0},
                        {0, -1}
                },
        };
        for (const auto& pair : cornerSteps) {
            const auto firstRow = static_cast<int>(cell.row) + pair.first.rowDiff;
            const auto firstColumn = static_cast<int>(cell.column) + pair.first.columnDiff;
            const auto secondRow = static_cast<int>(cell.row) + pair.second.rowDiff;
            const auto secondColumn = static_cast<int>(cell.column) + pair.second.columnDiff;

            const bool firstIn = firstRow >= 0 && firstRow < static_cast<int>(table.rowCount()) &&
                    firstColumn >= 0 && firstColumn < static_cast<int>(table.columnCount()) &&
                    table(firstRow, firstColumn) == region.value;
            const bool secondIn = secondRow >= 0 && secondRow < static_cast<int>(table.rowCount()) &&
                    secondColumn >= 0 && secondColumn < static_cast<int>(table.columnCount()) &&
                    table(secondRow, secondColumn) == region.value;
            if (!firstIn && !secondIn) {
                region.corners++;
            } else if (firstIn && secondIn) {
                const auto thirdRow = static_cast<int>(cell.row) + pair.first.rowDiff + pair.second.rowDiff;
                const auto thirdColumn = static_cast<int>(cell.column) + pair.first.columnDiff + pair.second.columnDiff;
                const bool thirdIn = thirdRow >= 0 && thirdRow < static_cast<int>(table.rowCount()) &&
                        thirdColumn >= 0 && thirdColumn < static_cast<int>(table.columnCount()) &&
                        table(thirdRow, thirdColumn) == region.value;
                if (!thirdIn) {
                    region.corners++;
                }
            }
        }
    }
}

void task1() {
    const auto table = file::readTable<char>("input.txt");
    Table<bool> visited(table.rowCount(), table.columnCount(), false);

    std::vector<TableRegion<char>> regions;
    for (size_t i = 0; i < table.rowCount(); i++) {
        for (size_t j = 0; j < table.columnCount(); j++) {
            if (!visited(i, j)) {
                std::queue<TableCell> lookupCells;
                lookupCells.push({i, j});

                TableRegion<char> region {
                    .value = table(i, j)
                };
                regions.push_back(std::move(region));

                determineRegion(regions.back(), table, visited, lookupCells);
            }
        }
    }

    long long price = 0;
    for (const auto& region : regions) {
        price += region.cells.size() * region.perimeter;
    }
    std::cout << "Price: " << price << std::endl;
}

void task2() {
    const auto table = file::readTable<char>("input.txt");
    Table<bool> visited(table.rowCount(), table.columnCount(), false);

    std::vector<TableRegion<char>> regions;
    for (size_t i = 0; i < table.rowCount(); i++) {
        for (size_t j = 0; j < table.columnCount(); j++) {
            if (!visited(i, j)) {
                std::queue<TableCell> lookupCells;
                lookupCells.push({i, j});

                TableRegion<char> region {
                        .value = table(i, j)
                };
                regions.push_back(std::move(region));

                determineRegion(regions.back(), table, visited, lookupCells);
            }
        }
    }

    // Print region type, area, perimeter and corners
    for (const auto& region : regions) {
        std::cout << "Region type: " << region.value << std::endl;
        std::cout << "Area: " << region.cells.size() << std::endl;
        std::cout << "Perimeter: " << region.perimeter << std::endl;
        std::cout << "Corners: " << region.corners << std::endl;
        std::cout << "-----------" << std::endl;
    }

    long long price = 0;
    for (const auto& region : regions) {
        price += region.cells.size() * region.corners;
    }
    std::cout << "Price: " << price << std::endl;
}

int main() {
    std::cout << "Task 1: " << std::endl;
    //task1(); // 1533644
    std::cout << "-----------" << std::endl;

    std::cout << "Task 2: " << std::endl;
    task2(); // 936718
    std::cout << "-----------" << std::endl;
    return 0;
}
