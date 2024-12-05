#include <iostream>
#include "common/file.h"
#include "common/parse.h"

void task1() {
    const auto table = file::readAsRows<char>("input.txt");

    // horizontal
    int horCount = 0;
    int horCountReverse = 0;
    for (const auto& row : table) {
        const auto str = std::string(row.begin(), row.end());
        horCount += parse::countSubstrings(str, "XMAS");
        horCountReverse += parse::countSubstringsInReverse(str, "XMAS");
    }

    // vertical
    std::vector<std::string> columns(table[0].size());
    for (size_t row = 0; row < table.size(); ++row) {
        for (size_t col = 0; col < table[row].size(); ++col) {
            columns[col] += table[row][col];
        }
    }
    int verCount = 0;
    int verCountReverse = 0;
    for (const auto& col : columns) {
        verCount += parse::countSubstrings(col, "XMAS");
        verCountReverse += parse::countSubstringsInReverse(col, "XMAS");
    }

    // diagonal second
    std::vector<std::string> diagonalsSecond(table.size() + table[0].size() - 1);
    for (size_t row = 0; row < table.size(); ++row) {
        for (size_t col = 0; col < table[row].size(); ++col) {
            diagonalsSecond[row + col] += table[row][col];
        }
    }
    int diagCountSecond = 0;
    int diagCountSecondReverse = 0;
    for (const auto& diagonal : diagonalsSecond) {
        diagCountSecond += parse::countSubstrings(diagonal, "XMAS");
        diagCountSecondReverse += parse::countSubstringsInReverse(diagonal, "XMAS");
    }

    // diagonal first
    std::vector<std::string> diagonalsFirst(table.size() + table[0].size() - 1);
    for (size_t row = 0; row < table.size(); ++row) {
        for (size_t col = 0; col < table[row].size(); ++col) {
            diagonalsFirst[row + table[row].size() - col - 1] += table[row][col];
        }
    }
    int diagCountFirst = 0;
    int diagCountFirstReverse = 0;
    for (const auto& diagonal : diagonalsFirst) {
        diagCountFirst += parse::countSubstrings(diagonal, "XMAS");
        diagCountFirstReverse += parse::countSubstringsInReverse(diagonal, "XMAS");
    }

    const auto totalCount = horCount + horCountReverse + verCount + verCountReverse + diagCountSecond + diagCountSecondReverse + diagCountFirst + diagCountFirstReverse;

    std::cout << "XMAS count: " << totalCount  << std::endl;
}

void task2() {
    const auto table = file::readAsRows<char>("input.txt");
    int count = 0;

    for (size_t row = 1; row < table.size() - 1; ++row) {
        for (size_t col = 1; col < table[row].size() - 1; ++col) {
            if (table[row][col] != 'A') {
                continue;
            }

            const auto lt = table[row - 1][col - 1];
            const auto rb = table[row + 1][col + 1];
            const auto lb = table[row + 1][col - 1];
            const auto rt = table[row - 1][col + 1];

            if (!((lt == 'M' && rb == 'S') || (lt == 'S' && rb == 'M'))) {
                continue;
            }

            if (!((lb == 'M' && rt == 'S') || (lb == 'S' && rt == 'M'))) {
                continue;
            }

            count++;
        }
    }

    std::cout << "X-MAS count: " << count << std::endl;
}

int main() {
    task1(); // 2562
    task2(); // 1902
    return 0;
}
