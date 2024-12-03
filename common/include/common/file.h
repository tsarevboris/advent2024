#include <string>
#include <vector>

namespace file {
    std::string readFileAsString(std::string_view path);
    std::vector<std::vector<int>> readFileAsVectorOfVectors(std::string_view path);
}
