#pragma once

#include <string>
#include <optional>

namespace parse {
    bool isDigit(char c);
    int getDigit(char c);

    bool checkCharAndMove(std::string_view input, char target, size_t& pos);
    bool findStringAndMove(std::string_view input, std::string_view target, size_t& pos);
    std::optional<int> readNumberAndMove(std::string_view input, size_t& pos, int maxDigits = 10);

    int countSubstrings(std::string_view input, std::string_view target);
    int countSubstringsInReverse(std::string_view input, std::string_view target);
}
