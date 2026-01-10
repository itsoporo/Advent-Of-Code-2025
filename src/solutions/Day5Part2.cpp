#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <array>

using Range = std::array<long long , 2>;
using RangeList = std::vector<Range>;

int main() {
    // accessing the file using ifstream, writing is ofstream
    std::ifstream PuzzleInput("../inputs/Day5.txt");

    // getting food ranges
    RangeList foodIdRanges;

    std::string rowText;
    while (std::getline(PuzzleInput, rowText)) {
        int dashStart = rowText.find('-');
        if (dashStart == std::string::npos) break;

        long long startingNumber = std::stoll(rowText.substr(0, dashStart));
        long long endingNumber = std::stoll(rowText.substr(dashStart + 1));

        long long leftMost = startingNumber;
        long long rightMost = endingNumber;
        
        // anything colliding with this range will merge
        for (int i = 0; i < foodIdRanges.size(); i++) {
            
            // in bound
            if ((startingNumber <= foodIdRanges[i][0] && foodIdRanges[i][0] <= endingNumber) 
            || (startingNumber <= foodIdRanges[i][1] && foodIdRanges[i][1] <= endingNumber)
            || (foodIdRanges[i][0] <= startingNumber && startingNumber <= foodIdRanges[i][1])) { // this statements accounts for if the current id range is entirely inside an existing id range
                // combining largest and smallest of both sides
                leftMost = std::min(foodIdRanges[i][0], leftMost);
                rightMost = std::max(foodIdRanges[i][1], rightMost);

                // deleteing old
                foodIdRanges.erase(foodIdRanges.begin() + i);
                i--;
                }
        }
        
        // replace those 
        foodIdRanges.push_back({leftMost, rightMost});
    }

    long long freshIds = 0;
    // accounting for the spaces
    for (const auto& [starting, ending] : foodIdRanges) {
        freshIds += ending - starting + 1; // fence post problem, we add 1 to account for posts so its inclusive
    }

    // Printing the output
    std::cout << freshIds << "\n";

    PuzzleInput.close();
}