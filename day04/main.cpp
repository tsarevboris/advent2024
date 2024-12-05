#include <iostream>
#include "common/file.h"

int countSubstrings(const std::string& str, const std::string& subStr) {
    int count = 0;
    size_t pos = 0;

    // Loop to find all occurrences of subStr in str
    while ((pos = str.find(subStr, pos)) != std::string::npos) {
        count++;
        pos += subStr.length();  // Move past the last found substring
    }

    return count;
}

int countSubstringsInReverse(const std::string& str, const std::string& subStr) {
    // Reverse the string
    std::string reversedStr = str;
    std::reverse(reversedStr.begin(), reversedStr.end());

    int count = 0;
    size_t pos = 0;

    // Loop to find all occurrences of subStr in the reversed string
    while ((pos = reversedStr.find(subStr, pos)) != std::string::npos) {
        count++;
        pos += subStr.length();  // Move past the last found substring
    }

    return count;
}

void task1() {
    const auto table = file::readAsCharRows("input.txt");

    // horizontal
    int horCount = 0;
    int horCountReverse = 0;
    for (const auto& row : table) {
        const auto str = std::string(row.begin(), row.end());
        horCount += countSubstrings(str, "XMAS");
        horCountReverse += countSubstringsInReverse(str, "XMAS");
    }

    std::cout << "hor count " << horCount << std::endl;
    std::cout << "hor count reverse " << horCountReverse << std::endl;

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
        verCount += countSubstrings(col, "XMAS");
        verCountReverse += countSubstringsInReverse(col, "XMAS");
    }

    std::cout << "ver count " << verCount << std::endl;
    std::cout << "ver count reverse " << verCountReverse << std::endl;

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
        diagCountSecond += countSubstrings(diagonal, "XMAS");
        diagCountSecondReverse += countSubstringsInReverse(diagonal, "XMAS");
    }

    std::cout << "diag count second " << diagCountSecond << std::endl;
    std::cout << "diag count second reverse " << diagCountSecondReverse << std::endl;

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
        diagCountFirst += countSubstrings(diagonal, "XMAS");
        diagCountFirstReverse += countSubstringsInReverse(diagonal, "XMAS");
    }

    std::cout << "diag count first " << diagCountFirst << std::endl;
    std::cout << "diag count first reverse " << diagCountFirstReverse << std::endl;

    const auto totalCount = horCount + horCountReverse + verCount + verCountReverse + diagCountSecond + diagCountSecondReverse + diagCountFirst + diagCountFirstReverse;

    std::cout << "XMAS count: " << totalCount  << std::endl;
}

void task2() {
    const auto table = file::readAsCharRows("input.txt");
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

    std::cout << "task 2 count: " << count << std::endl;
}

int main() {
    task1();
    task2();
    return 0;
}
