#include <string>
#include <vector>

namespace file {
    std::string readAsString(std::string_view path);
    std::vector<std::vector<int>> readAsColumns(std::string_view path);
    std::vector<std::vector<int>> readAsRows(std::string_view path);
}