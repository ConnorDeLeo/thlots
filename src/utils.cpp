#include "utils.hpp"

int utils::findVectorIndex(const std::vector<int> inputVector, int searchVal) {
    auto it = std::find(inputVector.begin(), inputVector.end(), searchVal);
    if (it != inputVector.end()) {
        return std::distance(inputVector.begin(), it); // return index
    }
    return -1; // not found
}