#include <iostream>
#include "common/file.h"
#include "common/parse.h"
#include <unordered_map>
#include <map>

enum Op {
    AND = 0,
    OR = 1,
    XOR = 2,
};

struct Gate {
    std::string input1;
    std::string input2;
    Op op;
    std::string output;
    bool fired = false;
};

struct Wire {
    std::string name;
    bool value;
};

void readData(std::unordered_map<std::string, bool>& wires, std::vector<Gate>& gates) {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening file " << "input.txt" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue;  // Skip empty lines
        }

        if (line.find("->") != std::string::npos) {
            Gate gate;
            size_t pos = 0;
            gate.input1 = line.substr(pos, 3);
            pos += 4;

            const std::string operation =  line.substr(pos, 3);
            if (operation.starts_with("AND")) {
                gate.op = Op::AND;
                pos += 4;
            } else if (operation.starts_with("OR")) {
                gate.op = Op::OR;
                pos += 3;
            } else if (operation.starts_with("XOR")) {
                gate.op = Op::XOR;
                pos += 4;
            }

            gate.input2 = line.substr(pos, 3);
            pos += 7;

            gate.output = line.substr(pos, 3);

            gates.push_back(gate);
        } else {
            size_t pos = 0;
            const std::string name = line.substr(pos, 3);
            pos += 5;

            const bool value = line.substr(pos, 1) == "1";

            wires[name] = value;
        }
    }
}

void produceValues(std::unordered_map<std::string, bool>& wires, std::vector<Gate>& gates) {
    while (true) {
        bool changed = false;
        // sort gates
        std::sort(gates.begin(), gates.end(), [](const Gate& a, const Gate& b) {
            return a.input1 < b.input1;
        });

        for (auto& gate : gates) {
            if (!gate.fired && wires.contains(gate.input1) && wires.contains(gate.input2)) {
                bool value1 = wires[gate.input1];
                bool value2 = wires[gate.input2];
                bool result = false;
                switch (gate.op) {
                    case Op::AND:
                        result = value1 & value2;
                        break;
                    case Op::OR:
                        result = value1 | value2;
                        break;
                    case Op::XOR:
                        result = value1 ^ value2;
                        break;
                }

                wires[gate.output] = result;
                gate.fired = true;
                changed = true;

                const auto opStr = gate.op == Op::AND ? "AND" : gate.op == Op::OR ? "OR" : "XOR";
                std::cout << gate.input1 << " " << opStr << " " << gate.input2 << " -> " << gate.output << std::endl;
            }
        }
        std::cout << "----------------" << std::endl;
        if (!changed) {
            break;
        }
    }
}

long long getNum(const std::unordered_map<std::string, bool>& wires, const std::string& name) {
    std::map<std::string, bool> numWires;
    for (const auto& [key, value] : wires) {
        if (key.starts_with(name)) {
            numWires[key] = value;
        }
    }

    long long result = 0;
    for (auto it = numWires.rbegin(); it != numWires.rend(); ++it) {
        result = (result << 1) | it->second;
    }
    return result;
}

void printBinary(long long num) {
    std::string binary;
    while (num > 0) {
        binary = std::to_string(num % 2) + binary;
        num /= 2;
    }
    std::cout << binary << std::endl;
}

void task1() {
    std::unordered_map<std::string, bool> wires;
    std::vector<Gate> gates;
    readData(wires, gates);

    // Produce all wire values
    produceValues(wires, gates);

    const auto result = getNum(wires, "z");
    std::cout << "Result: " << result << std::endl;
}

void task2() {
    std::unordered_map<std::string, bool> wires;
    std::vector<Gate> gates;
    readData(wires, gates);

    const auto x = getNum(wires, "x");
    const auto y = getNum(wires, "y");
    const auto correctSum = x + y;

    for (auto& gate : gates) {
        if (gate.output == "z37") {
            gate.output = "rrn";
        } else if (gate.output == "rrn") {
            gate.output = "z37";
        } else if (gate.output == "fkb") {
            gate.output = "z16";
        } else if (gate.output == "z16") {
            gate.output = "fkb";
        } else if (gate.output == "z31") {
            gate.output = "rdn";
        } else if (gate.output == "rdn") {
            gate.output = "z31";
        } else if (gate.output == "nnr") {
            gate.output = "rqf";
        } else if (gate.output == "rqf") {
            gate.output = "nnr";
        }
    }

//    for (size_t i = 0; i < gates.size(); ++i) {
//        if (gates[i].output == "z31") {
//            for (size_t j = 0; j < gates.size(); ++j) {
//                if (gates[j].output != "z31") {
//                    auto gatesCopy = gates;
//                    auto wiresCopy = wires;
//                    std::cout << gates[j].output;
//                    std::swap(gatesCopy[i].output, gatesCopy[j].output);
//                    produceValues(wiresCopy, gatesCopy);
//                    printBinary(correctSum);
//                    printBinary(getNum(wiresCopy, "z"));
//                    std::cout << "----------------" << std::endl;
//                }
//            }
//            break;
//        }
//    }

    produceValues(wires, gates);
    const auto z = getNum(wires, "z");

    std::cout << "Correct sum: " << correctSum << std::endl;
    std::cout << "Result: " << z << std::endl;

    printBinary(correctSum);
    printBinary(z);

 //Try to swap 2 pairs of wires so that system product correct sum with z-wires
//    while (true) {
//        for (size_t swap1 = 0; swap1 < gates.size(); ++swap1) {
//            std::cout << "Swap1: " << swap1 << std::endl;
//            for (size_t swap2 = swap1 + 1; swap2 < gates.size(); ++swap2) {
//                std::vector<Gate> gatesCopy = gates;
//                std::unordered_map<std::string, bool> wiresCopy = wires;
//
//                std::swap(gatesCopy[swap1].output, gatesCopy[swap2].output);
//
//                produceValues(wiresCopy, gatesCopy);
//                const auto z = getNum(wiresCopy, "z");
//                if (z == correctSum) {
//                    std::cout << "Correct sum found" << std::endl;
//                    std::cout << "Swap1: " << gates[swap1].output << " Swap2: " << gates[swap2].output << std::endl;
//                }
//            }
//        }
//    }
}

int main() {
    std::cout << "Task 1: " << std::endl;
    //task1();
    std::cout << "-----------" << std::endl;

    std::cout << "Task 2: " << std::endl;
    task2();
    std::cout << "-----------" << std::endl;
    return 0;
}

//// Try to swap 4 pairs of wires so that system product correct sum with z-wires
//while (true) {
//for (size_t swap1 = 0; swap1 < gates.size(); ++swap1) {
//std::cout << "Swap1: " << swap1 << std::endl;
//for (size_t swap2 = swap1 + 1; swap2 < gates.size(); ++swap2) {
//std::cout << "Swap2: " << swap2 << std::endl;
//for (size_t swap3 = swap1 + 1; swap3 < gates.size() && swap3 != swap2; ++swap3) {
//for (size_t swap4 = swap1 + 1; swap4 < gates.size() && swap4 != swap3 && swap4 != swap2; ++swap4) {
//for (size_t swap5 = swap1 + 1; swap5 < gates.size() && swap5 != swap4 && swap5 != swap3 && swap5 != swap2; ++swap5) {
//for (size_t swap6 = swap1 + 1; swap6 < gates.size() && swap6 != swap5 && swap6 != swap4 && swap6 != swap3 && swap6 != swap2; ++swap6) {
//for (size_t swap7 = swap1 + 1; swap7 < gates.size() && swap7 != swap6 && swap7 != swap5 && swap7 != swap4 && swap7 != swap3 && swap7 != swap2; ++swap7) {
//for (size_t swap8 = swap1 + 1; swap8 < gates.size() && swap8 != swap7 && swap8 != swap6 && swap8 != swap5 && swap8 != swap4 && swap8 != swap3 && swap8 != swap2; ++swap8) {
//std::vector<Gate> gatesCopy = gates;
//std::unordered_map<std::string, bool> wiresCopy = wires;
//
//std::swap(gatesCopy[swap1].output, gatesCopy[swap2].output);
//std::swap(gatesCopy[swap3].output, gatesCopy[swap4].output);
//std::swap(gatesCopy[swap5].output, gatesCopy[swap6].output);
//std::swap(gatesCopy[swap7].output, gatesCopy[swap8].output);
//
//produceValues(wiresCopy, gatesCopy);
//const auto z = getNum(wiresCopy, "z");
//if (z == correctSum) {
//std::cout << "Correct sum found" << std::endl;
//std::cout << "Swap1: " << swap1 << " Swap2: " << swap2 << " Swap3: " << swap3 << " Swap4: " << swap4 << " Swap5: " << swap5 << " Swap6: " << swap6 << " Swap7: " << swap7 << " Swap8: " << swap8 << std::endl;
//return;
//}
//}
//}
//}
//}
//}
//}
//}
//}
//}
