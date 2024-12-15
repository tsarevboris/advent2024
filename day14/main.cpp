#include <iostream>
#include "common/file.h"
#include "common/parse.h"

struct Robot {
    int x;
    int y;
    int vX;
    int vY;
};

std::vector<Robot> readRobots(std::string_view file) {
    std::ifstream inputFile(file);
    if (!inputFile) {
        std::cerr << "Error opening file " << file << std::endl;
        return {};
    }

    std::vector<Robot> robots;
    std::string line;
    while (std::getline(inputFile, line)) {
        Robot robot;

        size_t pos = 2;
        robot.x = parse::readNumberAndMove(line, pos).value();
        pos += 1;
        robot.y = parse::readNumberAndMove(line, pos).value();
        pos += 3;
        robot.vX = parse::readNumberAndMove(line, pos).value();
        pos += 1;
        robot.vY = parse::readNumberAndMove(line, pos).value();

        robots.push_back(robot);
    }

    return robots;
}



void task1() {
    auto robots = readRobots("input.txt");

    // print robots
//    for (const auto& robot : robots) {
//        std::cout << "Robot at (" << robot.x << ", " << robot.y << ") with velocity (" << robot.vX << ", " << robot.vY << ")" << std::endl;
//    }

    // Move robots
    const int maxSeconds = 100;
    const int fieldWidth = 101;
    const int fieldHeight = 103;

    for (auto& robot : robots) {
        robot.x = (robot.x + robot.vX * maxSeconds) % fieldWidth;
        robot.y = (robot.y + robot.vY * maxSeconds) % fieldHeight;

        if (robot.x < 0) {
            robot.x += fieldWidth;
        }
        if (robot.y < 0) {
            robot.y += fieldHeight;
        }
    }

    // print robots
//    for (const auto& robot : robots) {
//        std::cout << "Robot at (" << robot.x << ", " << robot.y << ") with velocity (" << robot.vX << ", " << robot.vY << ")" << std::endl;
//    }

    int sumTopLeft = 0;
    int sumTopRight = 0;
    int sumBottomLeft = 0;
    int sumBottomRight = 0;

    for (const auto& robot : robots) {
        if (robot.x < fieldWidth / 2 && robot.y < fieldHeight / 2) {
            sumTopLeft++;
        } else if (robot.x > fieldWidth / 2 && robot.y < fieldHeight / 2) {
            sumTopRight++;
        } else if (robot.x < fieldWidth / 2 && robot.y > fieldHeight / 2) {
            sumBottomLeft++;
        } else if (robot.x > fieldWidth / 2 && robot.y > fieldHeight / 2) {
            sumBottomRight++;
        }
    }

    std::cout << "Top left: " << sumTopLeft << std::endl;
    std::cout << "Top right: " << sumTopRight << std::endl;
    std::cout << "Bottom left: " << sumBottomLeft << std::endl;
    std::cout << "Bottom right: " << sumBottomRight << std::endl;

    std::cout << "Safety: " << sumTopLeft * sumTopRight * sumBottomLeft * sumBottomRight << std::endl;
}

bool checkTree(const std::vector<std::vector<int>>& field) {
    std::vector<int> longestRows(field[0].size());
    for (int y = 0; y < static_cast<int>(field[0].size()); y++) {
        bool found = false;
        int sequence = 0;
        for (int x = 0; x < static_cast<int>(field.size()); x++) {
            if (field[x][y] > 0) {
                found = true;
                sequence++;
            } else {
                if (found) {
                    longestRows[y] = std::max(longestRows[y], sequence);
                    sequence = 0;
                    found = false;
                }
            }
        }
    }

    std::reverse(longestRows.begin(), longestRows.end());
    // find max in longestRows
    int max = *std::max_element(longestRows.begin(), longestRows.end());
    if (max < 10) {
        return false;
    }

    // Find longest sequence of rows with diff exactly 2
    int longestSequence = 0;
    for (int i = 0; i < static_cast<int>(longestRows.size()); i++) {
        int sequence = 0;
        for (int j = i + 1; j < static_cast<int>(longestRows.size()); j++) {
            if (longestRows[i] - longestRows[j] == 2) {
                sequence++;
            } else {
                break;
            }
        }
        longestSequence = std::max(longestSequence, sequence);
    }

    return longestSequence >= 3;
}


void task2() {
    auto robots = readRobots("input.txt");

    // Move robots
    const int fieldWidth = 101;
    const int fieldHeight = 103;

    std::vector<std::vector<int>> field(fieldWidth, std::vector<int>(fieldHeight, 0));
    for (auto& robot : robots) {
        field[robot.x][robot.y]++;
    }

    int seconds = 0;
//    int maxSeconds = 500;
    while (true) {
        // Move robots
        for (auto &robot: robots) {
            field[robot.x][robot.y]--;
            robot.x = (robot.x + robot.vX) % fieldWidth;
            robot.y = (robot.y + robot.vY) % fieldHeight;

            if (robot.x < 0) {
                robot.x += fieldWidth;
            }
            if (robot.y < 0) {
                robot.y += fieldHeight;
            }

            field[robot.x][robot.y]++;
        }
        seconds++;

//        if (seconds > maxSeconds) {
//            break;
//        }

        // Print table for debugging
        if (checkTree(field)) {
            for (int y = 0; y < fieldHeight; y++) {
                for (int x = 0; x < fieldWidth; x++) {
                    std::cout << (field[x][y] > 0 ? "*" : " ");
                }
                std::cout << std::endl;
            }

            std::cout << std::endl;
            std::cout << std::endl;
            std::cout << "Seconds: " << seconds << std::endl;
        }
    }

    std::cout << "Seconds: " << seconds << std::endl;
}

int main() {
    std::cout << "Task 1: " << std::endl;
    //task1(); // 230172768
    std::cout << "-----------" << std::endl;

    std::cout << "Task 2: " << std::endl;
    task2();
    std::cout << "-----------" << std::endl;
    return 0;
}
