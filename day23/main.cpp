#include <iostream>
#include "common/file.h"
#include <unordered_map>
#include <unordered_set>
#include <set>

std::unordered_map<std::string, std::unordered_set<std::string>> readData(const std::string& filename) {
    std::unordered_map<std::string, std::unordered_set<std::string>> data;
    std::ifstream file(filename);
    if (file.is_open()) {
        // read data in the format string-string
        std::string line;
        while (std::getline(file, line)) {
            const auto user1 = line.substr(0, 2);
            const auto user2 = line.substr(3);
            data[user1].insert(user2);
            data[user2].insert(user1);
        }
    }
    return data;
};

void task1() {
    // read file
    const auto data = readData("input.txt");

    std::set<std::set<std::string>> foundComb;

    int count = 0;
    std::unordered_set<std::string> visited;
    for (const auto& [user, friends] : data) {
        if (!user.starts_with('t')) {
            continue;
        }

        for (const auto& f : friends) {
            if (visited.contains(f)) {
                continue;
            }

            for (const auto& ff : data.at(f)) {
                if (visited.contains(ff)) {
                    continue;
                }

                if (ff != user && data.at(ff).contains(user)) {
                    const auto comb = std::set<std::string>{user, f, ff};
                    if (foundComb.contains(comb)) {
                        continue;
                    }

                    foundComb.insert(comb);
                    count++;
                }
            }
        }

        visited.insert(user);
    }

    std::cout << "Count: " << count << std::endl;
}

void findGroup(const std::unordered_map<std::string, std::unordered_set<std::string>>& data,
                 const std::string& user,
                 std::unordered_set<std::string>& group) {
    for (const auto& f : data.at(user)) {
        if (group.contains(f)) {
            continue;
        }

        bool friendOfAll = true;
        for (const auto& g : group) {
            if (!data.at(g).contains(f)) {
                friendOfAll = false;
                break;
            }
        }

        if (friendOfAll) {
            group.insert(f);
            findGroup(data, f, group);
        }
    }
}

void task2() {
    const auto data = readData("input.txt");

    size_t maxGroupSize = 0;
    std::unordered_set<std::string> maxGroup;
    for (const auto& [user, friends] : data) {
        std::unordered_set<std::string> group;
        findGroup(data, user, group);
        if (group.size() > maxGroupSize) {
            maxGroupSize = group.size();
            maxGroup = group;
        }
    }

    // Print max group sorted alphabetically
    std::vector<std::string> sortedGroup(maxGroup.begin(), maxGroup.end());
    std::sort(sortedGroup.begin(), sortedGroup.end());
    for (const auto& user : sortedGroup) {
        std::cout << user << ",";
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Task 1: " << std::endl;
    task1(); // 1151
    std::cout << "-----------" << std::endl;

    std::cout << "Task 2: " << std::endl;
    task2(); // ar,cd,hl,iw,jm,ku,qo,rz,vo,xe,xm,xv,ys
    std::cout << "-----------" << std::endl;
    return 0;
}
