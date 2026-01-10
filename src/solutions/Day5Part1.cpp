#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <array>

using Range = std::array<long long , 2>;
using RangeList = std::vector<Range>;

bool isInListRange(RangeList &list, long long idCheck) {
    for (const auto& [rangeStart, rangeEnd] : list) {
        if (rangeStart <= idCheck && idCheck <= rangeEnd) return true; 
        // inclusive in puzzle
    }

    return false;
}

int main() {
    // accessing the file using ifstream, writing is ofstream
    std::ifstream PuzzleInput("../inputs/Day5.txt");

    std::vector<std::vector<int>> grid;

    int freshIds = 0;

    // getting food ranges
    RangeList foodIdRanges;

    std::string rowText;
    while (std::getline(PuzzleInput, rowText)) {
        int dashStart = rowText.find('-');
        if (dashStart == std::string::npos) break;

        long long startingNumber = std::stoll(rowText.substr(0, dashStart));
        long long endingNumber = std::stoll(rowText.substr(dashStart + 1));

        foodIdRanges.push_back(Range{startingNumber, endingNumber});
    }

    // checking food ids
    
    while (std::getline(PuzzleInput, rowText)) {
        long long foodId = std::stoll(rowText);

        if (isInListRange(foodIdRanges, foodId)) {
            freshIds++;
        }
    }

    // Printing the output
    std::cout << freshIds << "\n";

    PuzzleInput.close();
}