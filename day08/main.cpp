#include <iostream>
#include "common/file.h"
#include <vector>
#include <map>

struct Cell {
    int x;
    int y;
};

void task1() {
    auto table = file::readRows<char>("input.txt");

    std::map<char, std::vector<Cell>> groups;
    for (int i = 0; i < static_cast<int>(table.size()); i++) {
        for (int j = 0; j < static_cast<int>(table[i].size()); j++) {
            if (table[i][j] != '.') {
                groups[table[i][j]].push_back({i, j});
            }
        }
    }

    int count = 0;
    for (auto& [key, value] : groups) {
        for (int i = 0; i < static_cast<int>(value.size()); i++) {
            for (int j = i + 1; j < static_cast<int>(value.size()); j++) {
                // Calculate antinodes
                int xdiff = value[i].x - value[j].x;
                int ydiff = value[i].y - value[j].y;

                int antinode1x = value[i].x + xdiff;
                int antinode1y = value[i].y + ydiff;
                int antinode2x = value[j].x - xdiff;
                int antinode2y = value[j].y - ydiff;

                if (antinode1x >= 0 && antinode1x < static_cast<int>(table.size()) && antinode1y >= 0 && antinode1y < static_cast<int>(table[0].size())) {
                    if (table[antinode1x][antinode1y] != '#' ) {
                        table[antinode1x][antinode1y] = '#';
                        count++;
                    }
                }

                if (antinode2x >= 0 && antinode2x < static_cast<int>(table.size()) && antinode2y >= 0 && antinode2y < static_cast<int>(table[0].size())) {
                    if (table[antinode2x][antinode2y] != '#' ) {
                        table[antinode2x][antinode2y] = '#';
                        count++;
                    }
                }
            }
        }
    }

    // Print table
//    for (int i = 0; i < static_cast<int>(table.size()); i++) {
//        for (int j = 0; j < static_cast<int>(table[i].size()); j++) {
//            std::cout << table[i][j];
//        }
//        std::cout << std::endl;
//    }

    std::cout << count << std::endl;
}

void task2() {
    auto table = file::readRows<char>("input.txt");

    std::map<char, std::vector<Cell>> groups;
    for (int i = 0; i < static_cast<int>(table.size()); i++) {
        for (int j = 0; j < static_cast<int>(table[i].size()); j++) {
            if (table[i][j] != '.') {
                groups[table[i][j]].push_back({i, j});
            }
        }
    }

    int count = 0;
    for (auto& [key, value] : groups) {
        for (int i = 0; i < static_cast<int>(value.size()); i++) {
            for (int j = i + 1; j < static_cast<int>(value.size()); j++) {
                // Calculate antinodes
                int xdiff = value[i].x - value[j].x;
                int ydiff = value[i].y - value[j].y;

                if (std::abs(xdiff) == std::abs(ydiff)) {
                    xdiff = xdiff / std::abs(xdiff);
                    ydiff = ydiff / std::abs(ydiff);
                } else if (xdiff == 0) {
                    ydiff = ydiff / std::abs(ydiff);
                } else if (ydiff == 0) {
                    xdiff = xdiff / std::abs(xdiff);
                }

                int antinode1x = value[i].x;
                int antinode1y = value[i].y;
                int antinode2x = value[j].x;
                int antinode2y = value[j].y;

                while (true) {
                    antinode1x += xdiff;
                    antinode1y += ydiff;
                    if (antinode1x < 0 || antinode1x >= static_cast<int>(table.size()) || antinode1y < 0 || antinode1y >= static_cast<int>(table[0].size())) {
                        break;
                    }
                    if (table[antinode1x][antinode1y] != '#' ) {
                        table[antinode1x][antinode1y] = '#';
                        count++;
                    }
                }

                antinode1x = value[i].x;
                antinode1y = value[i].y;
                while (true) {
                    antinode1x -= xdiff;
                    antinode1y -= ydiff;
                    if (antinode1x < 0 || antinode1x >= static_cast<int>(table.size()) || antinode1y < 0 || antinode1y >= static_cast<int>(table[0].size())) {
                        break;
                    }
                    if (table[antinode1x][antinode1y] != '#' ) {
                        table[antinode1x][antinode1y] = '#';
                        count++;
                    }
                }

                while (true) {
                    antinode2x += xdiff;
                    antinode2y += ydiff;
                    if (antinode2x < 0 || antinode2x >= static_cast<int>(table.size()) || antinode2y < 0 || antinode2y >= static_cast<int>(table[0].size())) {
                        break;
                    }
                    if (table[antinode2x][antinode2y] != '#' ) {
                        table[antinode2x][antinode2y] = '#';
                        count++;
                    }
                }

                antinode2x = value[j].x;
                antinode2y = value[j].y;
                while (true) {
                    antinode2x -= xdiff;
                    antinode2y -= ydiff;
                    if (antinode2x < 0 || antinode2x >= static_cast<int>(table.size()) || antinode2y < 0 || antinode2y >= static_cast<int>(table[0].size())) {
                        break;
                    }
                    if (table[antinode2x][antinode2y] != '#' ) {
                        table[antinode2x][antinode2y] = '#';
                        count++;
                    }
                }
            }
        }
    }

    // Print table
    for (int i = 0; i < static_cast<int>(table.size()); i++) {
        for (int j = 0; j < static_cast<int>(table[i].size()); j++) {
            std::cout << table[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << count << std::endl;
}

int main() {
    task1();
    task2();
    return 0;
}
