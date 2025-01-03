#include <iostream>
#include "common/file.h"
#include <map>
#include <set>

struct Pos {
    int x;
    int y;

    bool operator==(const Pos& other) const {
        return x == other.x && y == other.y;
    }
    bool operator<(const Pos& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

static std::vector<std::string> testCodes = {
    "0",
};

static std::vector<int> testCodeValues = {
    1,
    980,
    179,
    456,
    379
};

static std::vector<std::string> codes = {
    "964A",
    "246A",
    "973A",
    "682A",
    "180A",
};

static std::vector<int> codeValues = {
    964,
    246,
    973,
    682,
    180
};

struct Pad {
    std::map<char, Pos> values;
    std::set<const Pos> poses;
};

static Pad numericPad = {
    {
        {'1', {0, 2}},
        {'2', {1, 2}},
        {'3', {2, 2}},
        {'4', {0, 1}},
        {'5', {1, 1}},
        {'6', {2, 1}},
        {'7', {0, 0}},
        {'8', {1, 0}},
        {'9', {2, 0}},
        {'0', {1, 3}},
        {'A', {2, 3}},
    },
    {{0, 2}, {1, 2}, {2, 2}, {0, 1}, {1, 1}, {2, 1}, {0, 0}, {1, 0}, {2, 0}, {1, 3}, {2, 3},}
};

static Pad directionalPad = {
    {
        {'<', {0, 1}},
        {'>', {2, 1}},
        {'^', {1, 0}},
        {'v', {1, 1}},
        {'A', {2, 0}},
    },
    {{0, 1}, {2, 1}, {1, 0}, {1, 1}, {2, 0},}
};

struct CharCost {
    char c;
    long long cost;
};

struct Cost {
    std::vector<CharCost> charCost;
    long long costToA;
};


Pos getDir(char c) {
    if (c == '<') {
        return {-1, 0};
    } else if (c == '>') {
        return {1, 0};
    } else if (c == '^') {
        return {0, -1};
    } else if (c == 'v') {
        return {0, 1};
    } else {
        return {0, 0};
    }
}

Cost getCost(char c) {
    if (c == 'A') {
        return {{{'^', 1}, {'>', 1}, {'v', 2}, {'<', 3}}, 0};
    } else if (c == '<') {
        return {{{'<', 0}, {'v', 1}, {'^', 2}, {'>', 2}}, 3};
    } else if (c == '>') {
        return {{{'>', 0}, {'v', 1}, {'<', 2}, {'^', 2}}, 1};
    } else if (c == '^') {
        return {{{'^', 0}, {'v', 1}, {'>', 2}, {'<', 2}}, 1};
    } else if (c == 'v') {
        return {{{'v', 0}, {'>', 1}, {'<', 1}, {'^', 1}}, 2};
    } else {
        return {};
    }
}

struct State {
    Pos pos;
    char lastChar; // Tracks the last character of the sequence
    long long currentCost;

    bool operator==(const State& other) const {
        return pos.x == other.pos.x && pos.y == other.pos.y &&
               lastChar == other.lastChar && currentCost == other.currentCost;
    }
};

// Custom hash function for State
struct StateHash {
    size_t operator()(const State& state) const {
        auto hash = std::hash<int>()(state.pos.x) ^ (std::hash<int>()(state.pos.y) << 1) ^
                    (std::hash<char>()(state.lastChar) << 2) ^ (std::hash<long long>()(state.currentCost) << 3);
        return hash;
    }
};

void move(const Pad& pad, std::vector<std::string>& paths, std::string seq, Pos pos, const Pos& targetPos, long long& minCost, long long currentCost,
          std::unordered_map<State, long long, StateHash>& memo) {
    const char lastChar = seq.empty() ? 'A' : seq.back();
    State currentState{pos, lastChar, currentCost};

    // Check if we already processed this state with a lower or equal cost
    if (memo.find(currentState) != memo.end() && memo[currentState] < currentCost) {
        return;
    }

    // Update memoization map
    memo[currentState] = currentCost;

    if (currentCost > minCost) {
        return;
    }

    if (pos.x == targetPos.x && pos.y == targetPos.y) {
        const auto cost = getCost(lastChar);
        seq.push_back('A');
        currentCost += cost.costToA;

        if (currentCost < minCost) {
            minCost = currentCost;
            paths.clear();
            paths.push_back(seq);
        } else if (currentCost == minCost) {
            paths.push_back(seq);
        }
        return;
    }

    const auto cost = getCost(lastChar);
    for (const auto& charCost : cost.charCost) {
        const auto dir = getDir(charCost.c);
        if (pos.x <= targetPos.x && dir.x < 0) {
            continue;
        }
        if (pos.x >= targetPos.x && dir.x > 0) {
            continue;
        }
        if (pos.y <= targetPos.y && dir.y < 0) {
            continue;
        }
        if (pos.y >= targetPos.y && dir.y > 0) {
            continue;
        }

        const auto nextPos = Pos{pos.x + dir.x, pos.y + dir.y};
        if (pad.poses.contains(nextPos)) {
            move(pad, paths, seq + charCost.c, nextPos, targetPos, minCost, currentCost + charCost.cost, memo);
            break;
        }
    }
}

std::vector<std::string> getPaths(const Pad& pad, const Pos& pos, char code) {
    std::vector<std::string> paths;
    const auto targetPos = pad.values.at(code);
    long long minCost = std::numeric_limits<long long>::max();
    std::unordered_map<State, long long, StateHash> memo;
    move(pad, paths, "", pos, targetPos, minCost, 0, memo);
    return paths;
}

enum class DirType {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    LEFT_UP,
    LEFT_DOWN,
    RIGHT_UP,
    RIGHT_DOWN,
};

constexpr int robotsCount = 25;

long long getDirectionalCost(DirType dirType, int robotNum, std::map<DirType, std::map<int, long long>>& memo) {
    if (robotNum == robotsCount) {
        switch (dirType) {
            case DirType::UP:
            case DirType::DOWN:
            case DirType::LEFT:
            case DirType::RIGHT:
                return 2;
            default:
                return 3;
        }
    }

    if (memo[dirType][robotNum] != 0) {
        return memo[dirType][robotNum];
    }

    long long cost = 0;

    switch (dirType) {
        case DirType::UP:
            cost = getDirectionalCost(DirType::LEFT, robotNum + 1, memo) +
                    getDirectionalCost(DirType::RIGHT, robotNum + 1, memo);
            break;
        case DirType::DOWN:
            cost = getDirectionalCost(DirType::LEFT_DOWN, robotNum + 1, memo) +
                    getDirectionalCost(DirType::UP_RIGHT, robotNum + 1, memo);
            break;
        case DirType::LEFT:
            cost = getDirectionalCost(DirType::DOWN_LEFT, robotNum + 1, memo) +
                    getDirectionalCost(DirType::RIGHT_UP, robotNum + 1, memo) + 2;
            break;
        case DirType::RIGHT:
            cost = getDirectionalCost(DirType::DOWN, robotNum + 1, memo) +
                    getDirectionalCost(DirType::UP, robotNum + 1, memo);
            break;
        case DirType::UP_LEFT:
            cost = getDirectionalCost(DirType::LEFT, robotNum + 1, memo) +
                    getDirectionalCost(DirType::DOWN_LEFT, robotNum + 1, memo) +
                    getDirectionalCost(DirType::RIGHT_UP, robotNum + 1, memo) + 1;
            break;
        case DirType::UP_RIGHT:
            cost = getDirectionalCost(DirType::LEFT, robotNum + 1, memo) +
                    getDirectionalCost(DirType::DOWN_RIGHT, robotNum + 1, memo) +
                    getDirectionalCost(DirType::UP, robotNum + 1, memo);
            break;
        case DirType::DOWN_LEFT:
            cost = getDirectionalCost(DirType::LEFT_DOWN, robotNum + 1, memo) +
                    getDirectionalCost(DirType::LEFT, robotNum + 1, memo) +
                    getDirectionalCost(DirType::RIGHT_UP, robotNum + 1, memo) + 1;
            break;
        case DirType::DOWN_RIGHT:
            cost = getDirectionalCost(DirType::LEFT_DOWN, robotNum + 1, memo) +
                    getDirectionalCost(DirType::RIGHT, robotNum + 1, memo) +
                    getDirectionalCost(DirType::UP, robotNum + 1, memo);
            break;
        case DirType::LEFT_UP:
            cost = getDirectionalCost(DirType::DOWN_LEFT, robotNum + 1, memo) +
                    getDirectionalCost(DirType::RIGHT_UP, robotNum + 1, memo) +
                    getDirectionalCost(DirType::RIGHT, robotNum + 1, memo) + 1;
            break;
        case DirType::LEFT_DOWN:
            cost = getDirectionalCost(DirType::DOWN_LEFT, robotNum + 1, memo) +
                    getDirectionalCost(DirType::RIGHT, robotNum + 1, memo) +
                    getDirectionalCost(DirType::UP_RIGHT, robotNum + 1, memo) + 1;
            break;
        case DirType::RIGHT_UP:
            cost = getDirectionalCost(DirType::DOWN, robotNum + 1, memo) +
                    getDirectionalCost(DirType::LEFT_UP, robotNum + 1, memo) +
                    getDirectionalCost(DirType::RIGHT, robotNum + 1, memo);
            break;
        case DirType::RIGHT_DOWN:
            cost = getDirectionalCost(DirType::DOWN, robotNum + 1, memo) +
                    getDirectionalCost(DirType::LEFT, robotNum + 1, memo) +
                    getDirectionalCost(DirType::UP_RIGHT, robotNum + 1, memo);
            break;
    }

    memo[dirType][robotNum] = cost;
    return cost;
}

long long getNumericCost(const Pos& pos, char code) {
    const auto targetPos = numericPad.values.at(code);
    DirType dirType;
    if (targetPos.x == pos.x) {
        dirType = pos.y < targetPos.y ? DirType::DOWN : DirType::UP;
    } else if (targetPos.y == pos.y) {
        dirType = pos.x < targetPos.x ? DirType::RIGHT : DirType::LEFT;
    } else if (targetPos.x > pos.x) {
        if (targetPos.y > pos.y) {
            dirType = (targetPos.y == 3 && pos.x == 0) ? DirType::RIGHT_DOWN : DirType::DOWN_RIGHT;
        } else {
            dirType = DirType::UP_RIGHT;
        }
    } else {
        if (targetPos.y > pos.y) {
            dirType = DirType::LEFT_DOWN;
        } else {
            dirType = (targetPos.x == 0 && pos.y == 3) ? DirType::UP_LEFT : DirType::LEFT_UP;
        }
    }

    const auto cost = std::max(std::abs(targetPos.x - pos.x) - 1, 0) + std::max(std::abs(targetPos.y - pos.y) - 1, 0);

    std::map<DirType, std::map<int, long long>> memo;
    return cost + getDirectionalCost(dirType, 0, memo);
}

long long getFullCost(const std::string& code) {
    long long cost = 0;
    Pos currentPos = numericPad.values.at('A');
    for (char c : code) {
        cost += getNumericCost(currentPos, c);
        currentPos = numericPad.values.at(c);
    }
    return cost;
}

std::vector<std::string> getFullPaths(const Pad& pad, const Pos& pos, const std::string& code) {
    std::vector<std::string> paths;
    Pos currentPos = pos;
    for (char c : code) {
        const auto targetPos = pad.values.at(c);
        auto p = getPaths(pad, currentPos, c);

        if (paths.empty()) {
            paths = std::move(p);
        } else {
            std::vector<std::string> newPaths;
            for (const auto& path : paths) {
                for (const auto& path2 : p) {
                    newPaths.push_back(path + path2);
                }
            }
            paths = std::move(newPaths);
        }

        currentPos = targetPos;
    }
    return paths;
}

std::vector<std::string> getAllFullPaths(const Pad& pad, const Pos& pos, const std::vector<std::string>& prevPaths) {
    std::vector<std::string> paths;
    for (const auto& code : prevPaths) {
        auto p = getFullPaths(pad, pos, code);
        paths.insert(paths.end(), p.begin(), p.end());
    }
    return paths;
}

void task1() {
    long long complexity = 0;
    for (size_t i = 0; i < codes.size(); ++i) {
        const auto code = codes[i];
        const auto pos = numericPad.values['A'];
        auto paths = getFullPaths(numericPad, pos, code);

        for (int robot = 0; robot < robotsCount; robot++) {
            paths = getAllFullPaths(directionalPad, directionalPad.values['A'], paths);
        }

        // Find the shortest path len
        long long minLen = std::numeric_limits<int>::max();
        for (const auto& path : paths) {
            minLen = std::min(minLen, static_cast<long long>(path.size()));
        }

        complexity += minLen * codeValues[i];
    }

    std::cout << "Complexity: " << complexity << std::endl;
}

void task2() {
    long long complexity = 0;
    for (size_t i = 0; i < codes.size(); ++i) {
        const auto code = codes[i];
        const auto cost = getFullCost(code);
        complexity += cost * codeValues[i];
    }

    std::cout << "Complexity: " << complexity << std::endl;
}

int main() {
    std::cout << "Task 1: " << std::endl;
    //task1(); // 212488
    std::cout << "-----------" << std::endl;

    std::cout << "Task 2: " << std::endl;
    task2(); // 258263972600402
    std::cout << "-----------" << std::endl;
    return 0;
}
