#include <iostream>
#include "common/file.h"

void moveRobots(Table<char>& table, std::vector<char>& movements) {
    // Find robot (symbol '@')
    int robotX = 0;
    int robotY = 0;
    for (int i = 0; i < static_cast<int>(table.rowCount()); i++) {
        for (int j = 0; j < static_cast<int>(table.columnCount()); j++) {
            if (table[i][j] == '@') {
                robotX = i;
                robotY = j;
                break;
            }
        }
    }

    // Move robot
    for (auto& movement : movements) {
        switch (movement) {
            case '^':
                if (robotX > 0 && table[robotX - 1][robotY] != '#') {
                    if (table[robotX - 1][robotY] == 'O') {
                        int x = robotX - 2;
                        while (x > 0 && table[x][robotY] != '#' && table[x][robotY] != '.') {
                            x--;
                        }
                        if (table[x][robotY] == '.') {
                            table[x][robotY] = 'O';
                        } else {
                            continue;
                        }
                    }

                    table[robotX][robotY] = '.';
                    robotX--;
                    table[robotX][robotY] = '@';
                }
                break;
            case 'v':
                if (robotX < static_cast<int>(table.rowCount() - 1) && table[robotX + 1][robotY] != '#') {
                    if (table[robotX + 1][robotY] == 'O') {
                        int x = robotX + 2;
                        while (x < static_cast<int>(table.rowCount() - 1) && table[x][robotY] != '#' && table[x][robotY] != '.') {
                            x++;
                        }
                        if (table[x][robotY] == '.') {
                            table[x][robotY] = 'O';
                        } else {
                            continue;
                        }
                    }

                    table[robotX][robotY] = '.';
                    robotX++;
                    table[robotX][robotY] = '@';
                }
                break;
            case '<':
                if (robotY > 0 && table[robotX][robotY - 1] != '#') {
                    if (table[robotX][robotY - 1] == 'O') {
                        int y = robotY - 2;
                        while (y > 0 && table[robotX][y] != '#' && table[robotX][y] != '.') {
                            y--;
                        }
                        if (table[robotX][y] == '.') {
                            table[robotX][y] = 'O';
                        } else {
                            continue;
                        }
                    }

                    table[robotX][robotY] = '.';
                    robotY--;
                    table[robotX][robotY] = '@';
                }
                break;
            case '>':
                if (robotY < static_cast<int>(table.columnCount() - 1) && table[robotX][robotY + 1] != '#') {
                    if (table[robotX][robotY + 1] == 'O') {
                        int y = robotY + 2;
                        while (y < static_cast<int>(table.columnCount() - 1) && table[robotX][y] != '#' && table[robotX][y] != '.') {
                            y++;
                        }
                        if (table[robotX][y] == '.') {
                            table[robotX][y] = 'O';
                        } else {
                            continue;
                        }
                    }

                    table[robotX][robotY] = '.';
                    robotY++;
                    table[robotX][robotY] = '@';
                }
                break;
        }
    }
}

int findSum(Table<char>& table) {
    int sum = 0;
    for (int row = 0; row < static_cast<int>(table.rowCount()); row++) {
        for (int col = 0; col < static_cast<int>(table.columnCount()); col++) {
            if (table[row][col] == 'O') {
                sum += row * 100 + col;
            }
        }
    }
    return sum;
}

int findSum2(Table<char>& table) {
    int sum = 0;
    for (int row = 0; row < static_cast<int>(table.rowCount()); row++) {
        for (int col = 0; col < static_cast<int>(table.columnCount()); col++) {
            if (table[row][col] == '[') {
                sum += row * 100 + col;
            }
        }
    }
    return sum;
}

void task1() {
    auto table = file::readTable<char>("input.txt");
    std::vector<char> movements;
    int movementsRowsCount = 0;
    for (auto& row : table) {
        if (row[0] == '<' || row[0] == '>' || row[0] == '^' || row[0] == 'v') {
            movements.insert(movements.end(), row.begin(), row.end());
        }
    }
    for (int i = 0; i < movementsRowsCount; ++i) {
        table.data.pop_back();
    }

    // print table
    for (auto& row : table) {
        for (auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    // print movements
    std::cout << std::endl << "Movements: ";
    for (auto& movement : movements) {
        std::cout << movement;
    }
    std::cout << std::endl;

    moveRobots(table, movements);
    const auto sum = findSum(table);

    // print sum
    std::cout << "Sum: " << sum << std::endl;
}

void updateWarehouse(Table<char>& table) {
    for (auto i = 0; i < static_cast<int>(table.rowCount()); ++i) {
        auto& row = table[i];
        row.reserve(row.size() * 2);
        for (auto it = row.begin(); it != row.end(); ++it) {
            if (*it == '#') {
                it++;
                row.insert(it, '#');
            } else if (*it == 'O') {
                *it = '[';
                it++;
                row.insert(it, ']');
            } else if (*it == '@' || *it == '.') {
                it++;
                row.insert(it, '.');
            }
        }
    }
}

struct Cell {
    int x;
    int y;

    bool operator==(const Cell& other) const {
        return x == other.x && y == other.y;
    }
};

void removeDuplicates(std::vector<Cell>& boxes) {
    for (auto it = boxes.begin(); it != boxes.end(); ++it) {
        for (auto it2 = it + 1; it2 != boxes.end(); ++it2) {
            if (*it == *it2) {
                boxes.erase(it2);
                it2--;
            }
        }
    }
}

void moveRobots2(Table<char>& table, std::vector<char>& movements) {
    // Find robot (symbol '@')
    int robotX = 0;
    int robotY = 0;
    for (int i = 0; i < static_cast<int>(table.rowCount()); i++) {
        for (int j = 0; j < static_cast<int>(table.columnCount()); j++) {
            if (table[i][j] == '@') {
                robotX = i;
                robotY = j;
                break;
            }
        }
    }

    // Move robot
    for (auto& movement : movements) {
        std::cout << "Movement " << movement << std::endl;
        switch (movement) {
            case '^':
                if (robotX > 0 && table[robotX - 1][robotY] != '#') {
                    // Find boxes
                    if (table[robotX - 1][robotY] == ']' || table[robotX - 1][robotY] == '[') {
                        std::vector<Cell> boxes;
                        if (table[robotX - 1][robotY] == '[') {
                            boxes.push_back({robotX - 1, robotY});
                            boxes.push_back({robotX - 1, robotY + 1});
                        } else {
                            boxes.push_back({robotX - 1, robotY});
                            boxes.push_back({robotX - 1, robotY - 1});
                        }

                        bool canMove = true;
                        size_t index = 0;
                        int lastBoxesCount = 2;
                        while (lastBoxesCount > 0) {
                            auto size = boxes.size();
                            lastBoxesCount = 0;
                            for (; index < size; index++) {
                                auto box = boxes[index];
                                if (table[box.x - 1][box.y] == '#') {
                                    canMove = false;
                                    break;
                                } else if (table[box.x - 1][box.y] == '.') {
                                    continue;
                                } else {
                                    lastBoxesCount += 2;
                                    if (table[box.x - 1][box.y] == '[') {
                                        boxes.push_back({box.x - 1, box.y});
                                        boxes.push_back({box.x - 1, box.y + 1});
                                    } else {
                                        boxes.push_back({box.x - 1, box.y});
                                        boxes.push_back({box.x - 1, box.y - 1});
                                    }
                                }
                            }
                        }

                        if (!canMove) {
                            continue;
                        }
                        removeDuplicates(boxes);

                        // Move boxes in reverse order
                        for (int i = boxes.size() - 1; i >= 0; i--) {
                            table[boxes[i].x - 1][boxes[i].y] = table[boxes[i].x][boxes[i].y];
                            table[boxes[i].x][boxes[i].y] = '.';
                        }
                    }

                    table[robotX][robotY] = '.';
                    robotX--;
                    table[robotX][robotY] = '@';
                }
                break;
            case 'v':
                if (robotX < static_cast<int>(table.rowCount() - 1) && table[robotX + 1][robotY] != '#') {
                    // Find robots
                    if (table[robotX + 1][robotY] == ']' || table[robotX + 1][robotY] == '[') {
                        std::vector<Cell> boxes;
                        if (table[robotX + 1][robotY] == '[') {
                            boxes.push_back({robotX + 1, robotY});
                            boxes.push_back({robotX + 1, robotY + 1});
                        } else {
                            boxes.push_back({robotX + 1, robotY});
                            boxes.push_back({robotX + 1, robotY - 1});
                        }

                        bool canMove = true;
                        size_t index = 0;
                        int lastBoxesCount = 2;
                        while (lastBoxesCount > 0) {
                            auto size = boxes.size();
                            lastBoxesCount = 0;
                            for (; index < size; index++) {
                                auto box = boxes[index];
                                if (table[box.x + 1][box.y] == '#') {
                                    canMove = false;
                                    break;
                                } else if (table[box.x + 1][box.y] == '.') {
                                    continue;
                                } else {
                                    lastBoxesCount += 2;
                                    if (table[box.x + 1][box.y] == '[') {
                                        boxes.push_back({box.x + 1, box.y});
                                        boxes.push_back({box.x + 1, box.y + 1});
                                    } else {
                                        boxes.push_back({box.x + 1, box.y});
                                        boxes.push_back({box.x + 1, box.y - 1});
                                    }
                                }
                            }
                        }

                        if (!canMove) {
                            continue;
                        }
                        removeDuplicates(boxes);

                        // Move boxes in reverse order
                        for (int i = boxes.size() - 1; i >= 0; i--) {
                            table[boxes[i].x + 1][boxes[i].y] = table[boxes[i].x][boxes[i].y];
                            table[boxes[i].x][boxes[i].y] = '.';
                        }
                    }

                    table[robotX][robotY] = '.';
                    robotX++;
                    table[robotX][robotY] = '@';
                }
                break;
            case '<':
                if (robotY > 0 && table[robotX][robotY - 1] != '#') {
                    // Found a box
                    if (table[robotX][robotY - 1] == ']') {
                        // Find first empty space
                        int y = robotY - 2;
                        while (y > 0 && table[robotX][y] != '#' && table[robotX][y] != '.') {
                            y--;
                        }
                        if (table[robotX][y] == '.') {
                            // Move boxes to the left
                            for (int i = y; i < robotY - 1; i++) {
                                table[robotX][i] = table[robotX][i + 1];
                            }
                        } else {
                            // No space - no robot movement
                            continue;
                        }
                    }

                    table[robotX][robotY] = '.';
                    robotY--;
                    table[robotX][robotY] = '@';
                }
                break;
            case '>':
                if (robotY < static_cast<int>(table.columnCount() - 1) && table[robotX][robotY + 1] != '#') {
                    if (table[robotX][robotY + 1] == '[') {
                        int y = robotY + 2;
                        while (y < static_cast<int>(table.columnCount() - 1) && table[robotX][y] != '#' && table[robotX][y] != '.') {
                            y++;
                        }
                        if (table[robotX][y] == '.') {
                            // Move boxes to the right
                            for (int i = y; i > robotY + 1; i--) {
                                table[robotX][i] = table[robotX][i - 1];
                            }
                        } else {
                            continue;
                        }
                    }

                    table[robotX][robotY] = '.';
                    robotY++;
                    table[robotX][robotY] = '@';
                }
                break;
        }

        // print table
//        for (auto& row : table) {
//            for (auto& cell : row) {
//                std::cout << cell << " ";
//            }
//            std::cout << std::endl;
//        }
    }
}

void task2() {
    auto table = file::readTable<char>("input.txt");
    std::vector<char> movements;
    int movementsRowsCount = 0;
    for (auto& row : table) {
        if (row[0] == '<' || row[0] == '>' || row[0] == '^' || row[0] == 'v') {
            movements.insert(movements.end(), row.begin(), row.end());
            movementsRowsCount++;
        }
    }
    for (int i = 0; i < movementsRowsCount; ++i) {
        table.data.pop_back();
    }

    updateWarehouse(table);

    // print table
    for (auto& row : table) {
        for (auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    // print movements
    std::cout << std::endl << "Movements: ";
    for (auto& movement : movements) {
        std::cout << movement;
    }
    std::cout << std::endl;

    moveRobots2(table, movements);
    const auto sum = findSum2(table);

    // print table
    for (auto& row : table) {
        for (auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }

    // print sum
    std::cout << "Sum: " << sum << std::endl;
}

int main() {
    std::cout << "Task 1: " << std::endl;
    //task1(); // 1413675
    std::cout << "-----------" << std::endl;

    std::cout << "Task 2: " << std::endl;
    task2();
    std::cout << "-----------" << std::endl;
    return 0;
}
