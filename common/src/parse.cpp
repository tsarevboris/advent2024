#include "common/parse.h"

namespace parse {
    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    int getDigit(char c) {
        return c - '0';
    }

    bool checkCharAndMove(std::string_view input, char target, size_t& pos) {
        if (pos >= input.size() || input[pos] != target) {
            return false;
        }
        pos++;
        return true;
    }

    bool findStringAndMove(std::string_view input, std::string_view target, size_t& pos) {
        pos = input.find(target, pos);
        if (pos == std::string::npos) {
            return false;
        }
        pos += target.size();
        return true;
    }

    std::optional<int> readNumberAndMove(std::string_view input, size_t& pos, int maxDigits) {
        int number = 0;
        int i = 0;
        bool negative = false;
        if (input[pos] == '-') {
            pos++;
            negative = true;
        }
        for (; i < maxDigits && pos < input.size() && isDigit(input[pos]); i++) {
            number = number * 10 + getDigit(input[pos]);
            pos++;
        }
        return i > 0 ? std::make_optional(negative ? -number : number) : std::nullopt;
    }

    std::optional<long long> readLongAndMove(std::string_view input, size_t& pos, int maxDigits) {
        long long number = 0;
        int i = 0;
        for (; i < maxDigits && pos < input.size() && isDigit(input[pos]); i++) {
            number = number * 10 + getDigit(input[pos]);
            pos++;
        }
        return i > 0 ? std::make_optional(number) : std::nullopt;
    }

    int countSubstrings(std::string_view input, std::string_view target) {
        int count = 0;
        size_t pos = 0;

        while ((pos = input.find(target, pos)) != std::string::npos) {
            count++;
            pos += target.length();
        }

        return count;
    }

    int countSubstringsInReverse(std::string_view input, std::string_view target) {
        std::string reversedInput{input};
        std::ranges::reverse(reversedInput);

        int count = 0;
        size_t pos = 0;

        while ((pos = reversedInput.find(target, pos)) != std::string::npos) {
            count++;
            pos += target.length();
        }

        return count;
    }
}
