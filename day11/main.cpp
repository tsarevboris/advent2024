#include <iostream>
#include "common/file.h"
#include <vector>
#include <string>
#include <map>
#include <list>

void getFirstAndSecondHalf(long long n, long long &firstHalf, long long &secondHalf) {
    if (n == 0) {
        firstHalf = 0;
        secondHalf = 0;
        return;
    }

    // Calculate the number of digits in n
    int totalDigits = 0;
    long long temp = n;
    while (temp > 0) {
        temp /= 10;
        totalDigits++;
    }

    // Determine the number of digits in each half
    int firstHalfDigits = totalDigits / 2;
    int secondHalfDigits = totalDigits - firstHalfDigits;

    // Calculate the divisor to split the number
    long long divisor = 1;
    for (int i = 0; i < secondHalfDigits; ++i) {
        divisor *= 10;
    }

    // Extract the first and second halves
    firstHalf = n / divisor;
    secondHalf = n % divisor;
}

int getDigitsNum(long long num) {
    static std::unordered_map<long long, int> cache;
    if (cache.contains(num)) {
        return cache[num];
    }
    int digitsNum = 0;
    while (num > 0) {
        num /= 10;
        digitsNum++;
    }
    cache[num] = digitsNum;
    return digitsNum;
}

int getDigitsNum2(long long num) {
    int digitsNum = 0;
    while (num > 0) {
        num /= 10;
        digitsNum++;
    }
    return digitsNum;
}

void blink(std::list<long long>& nums) {
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        if (*it == 0) {
            *it = 1;
        } else if (getDigitsNum(*it) % 2 == 0) {
            long long newNum1;
            long long newNum2;
            getFirstAndSecondHalf(*it, newNum1, newNum2);
            *it = newNum1;
            it++;
            it = nums.insert(it, newNum2);
        } else {
            *it = *it * 2024;
        }
    }
}

void blink2(std::map<long long, long long>& nums) {
    std::map<long long, long long> newMap;
    for (auto [num, count] : nums) {
        if (num == 0) {
            newMap[1] += count;
        } else if (getDigitsNum2(num) % 2 == 0) {
            long long newNum1;
            long long newNum2;
            getFirstAndSecondHalf(num, newNum1, newNum2);
            newMap[newNum1] += count;
            newMap[newNum2] += count;
        } else {
            newMap[num * 2024] += count;
        }
    }
    nums = std::move(newMap);
}

void task1() {
    const auto data = file::readAsRows<long long>("input.txt");
    std::list<long long> nums(data[0].begin(), data[0].end());

    std::cout << "data: ";
    for (const auto& num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    const auto blinksCount = 75;
    for (int i = 0; i < blinksCount; i++) {
        blink(nums);
        std::cout << "blinks: " << i << std::endl;
    }

    std::cout << "Stones count: " << nums.size() << std::endl;
}


void task2() {
    const auto data = file::readAsRows<long long>("input.txt");
    std::map<long long, long long> nums;
    for (const auto& num : data[0]) {
        nums[num]++;
    }

    const auto blinksCount = 75;
    for (int i = 0; i < blinksCount; i++) {
        blink2(nums);
        std::cout << "blinks: " << i + 1 << std::endl;
    }

    long long stonesCount = 0;
    for (const auto& [num, count] : nums) {
        stonesCount += count;
    }
    std::cout << "Stones count: " << stonesCount << std::endl;
}

int main() {
//    task1();
    task2();
    return 0;
}
