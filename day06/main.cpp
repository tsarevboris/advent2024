#include <iostream>
#include "common/file.h"

void task1() {
    auto map = file::readAsRows<char>("input.txt");

    // Find a guard
    int i = 0;
    int j = 0;
    bool found = false;
    for (i = 0; i < static_cast<int>(map.size()) && !found; i++) {
        for (j = 0; j < static_cast<int>(map[i].size()) && !found; j++) {
            if (map[i][j] == '^') {
                std::cout << "Guard found at (" << i << ", " << j << ")" << std::endl;
                found = true;
            }
        }
    }

    i--;
    j--;

    int positions = 1;
    const auto height = static_cast<int>(map.size());
    const auto width = static_cast<int>(map[0].size());

    // Find the path
    while (true) {
        if (map[i][j] == '^') {
            if (i == 0) {
                break;
            }
            if (map[i - 1][j] == '#') {
                map[i][j] = '>';
                //std::cout << "Turned right at (" << i << ", " << j << ")" << std::endl;
            } else {
                i--;
                if (map[i][j] == '.') {
                    positions++;
                }
                map[i][j] = '^';
                //std::cout << "Moved up to (" << i << ", " << j << ")" << std::endl;
            }
        } else if (map[i][j] == '>') {
            if (j == width - 1) {
                break;
            }
            if (map[i][j + 1] == '#') {
                map[i][j] = 'v';
                //std::cout << "Turned down at (" << i << ", " << j << ")" << std::endl;
            } else {
                j++;
                if (map[i][j] == '.') {
                    positions++;
                }
                map[i][j] = '>';
                //std::cout << "Moved right to (" << i << ", " << j << ")" << std::endl;
            }
        } else if (map[i][j] == 'v') {
            if (i == height - 1) {
                break;
            }
            if (map[i + 1][j] == '#') {
                map[i][j] = '<';
                //std::cout << "Turned left at (" << i << ", " << j << ")" << std::endl;
            } else {
                i++;
                if (map[i][j] == '.') {
                    positions++;
                }
                map[i][j] = 'v';
                //std::cout << "Moved down to (" << i << ", " << j << ")" << std::endl;
            }
        } else if (map[i][j] == '<') {
            if (j == 0) {
                break;
            }
            if (map[i][j - 1] == '#') {
                map[i][j] = '^';
                //std::cout << "Turned up at (" << i << ", " << j << ")" << std::endl;
            } else {
                j--;
                if (map[i][j] == '.') {
                    positions++;
                }
                map[i][j] = '<';
                //std::cout << "Moved left to (" << i << ", " << j << ")" << std::endl;
            }
        }
    }

    std::cout << "Positions count: " << positions << std::endl;
}

bool isStuck(std::vector<std::vector<char>>& map, int i, int j) {
    const auto height = static_cast<int>(map.size());
    const auto width = static_cast<int>(map[0].size());

    // Find the path
    bool stuck = false;
    char direction = '^';
    while (!stuck) {
        if (direction == '^') {
            if (i == 0) {
                break;
            }
            if (map[i - 1][j] == '#') {
                direction = '>';
                //std::cout << "Turned right at (" << i << ", " << j << ")" << std::endl;
            } else {
                i--;
                direction = '^';
                if (map[i][j] == direction) {
                    stuck = true;
                    break;
                }
                map[i][j] = direction;
                //std::cout << "Moved up to (" << i << ", " << j << ")" << std::endl;
            }
        } else if (direction == '>') {
            if (j == width - 1) {
                break;
            }
            if (map[i][j + 1] == '#') {
                direction = 'v';
                //std::cout << "Turned down at (" << i << ", " << j << ")" << std::endl;
            } else {
                j++;
                direction = '>';
                if (map[i][j] == direction) {
                    stuck = true;
                    break;
                }
                map[i][j] = direction;
                //std::cout << "Moved right to (" << i << ", " << j << ")" << std::endl;
            }
        } else if (direction == 'v') {
            if (i == height - 1) {
                break;
            }
            if (map[i + 1][j] == '#') {
                direction = '<';
               // std::cout << "Turned left at (" << i << ", " << j << ")" << std::endl;
            } else {
                i++;
                direction = 'v';
                if (map[i][j] == direction) {
                    stuck = true;
                    break;
                }
                map[i][j] = direction;
                //std::cout << "Moved down to (" << i << ", " << j << ")" << std::endl;
            }
        } else if (direction == '<') {
            if (j == 0) {
                break;
            }
            if (map[i][j - 1] == '#') {
                direction = '^';
                //std::cout << "Turned up at (" << i << ", " << j << ")" << std::endl;
            } else {
                j--;
                direction = '<';
                if (map[i][j] == direction) {
                    stuck = true;
                    break;
                }
                map[i][j] = direction;
                //std::cout << "Moved left to (" << i << ", " << j << ")" << std::endl;
            }
        }
    }

    return stuck;
}

void task2() {
    auto map = file::readAsRows<char>("input.txt");

    // Find a guard
    int i = 0;
    int j = 0;
    bool found = false;
    for (i = 0; i < static_cast<int>(map.size()) && !found; i++) {
        for (j = 0; j < static_cast<int>(map[i].size()) && !found; j++) {
            if (map[i][j] == '^') {
                std::cout << "Guard found at (" << i << ", " << j << ")" << std::endl;
                found = true;
            }
        }
    }
    i--;
    j--;

    int stuckCount = 0;
    for (int x = 0; x < static_cast<int>(map.size()); x++) {
        for (int y = 0; y < static_cast<int>(map[0].size()); y++) {
            if (map[x][y] == '.') {
                std::cout << "Checking stuck at (" << x << ", " << y << ")" << std::endl;
                auto mapCopy = map;
                mapCopy[x][y] = '#';
                if (isStuck(mapCopy, i, j)) {
                    stuckCount++;
                }
            }
        }
    }

    std::cout << "Stuck count: " << stuckCount << std::endl;
}

int main() {
    //task1();
    task2();
    return 0;
}
