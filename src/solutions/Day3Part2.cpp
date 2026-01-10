#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

int findIndex(int arr[], int target) {
    for (int i = 0; i < 12; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int findLargestIdx(std::string *rowText, int startIdx, int ignoreIdxs[]) {
    int largest = -1;
    int largestIdx = -1;
   
    // find right to left instead of left to right for case of 4040504
    for (int charIdx = startIdx; charIdx < (*rowText).size(); charIdx++) {
        if (findIndex(ignoreIdxs, charIdx) != -1) {
            continue;
        }
        // if (charIdx == ignoreIdx) continue;

        int parsed = (*rowText)[charIdx] - '0';

        // if not the starting largest number get right most largest instead of leftmost
        if (startIdx == 0 && parsed > largest || parsed >= largest) {
            largest = parsed;
            largestIdx = charIdx;
        }
    }

    return largestIdx;
}

int main() {
    // accessing the file using ifstream, writing is ofstream
    std::ifstream PuzzleInput("../inputs/Day3.txt");

    long long voltageSum = 0;

    std::string rowText;
    while (std::getline(PuzzleInput, rowText)) {
        int ignoringIds[12] = {};
        std::vector<int> possibleMatches = {};
        std::fill(ignoringIds, ignoringIds + 12, -1);

        int startingDigit = 0;

        for (int batteryIdx = 0; batteryIdx < 12; batteryIdx++) {
            int check = findLargestIdx(&rowText, startingDigit, ignoringIds);
            if (check == -1) { // meaning that all the right digits were taken
                startingDigit = 0; // reset and find a new largest one
            }

            int firstLargestIdx = findLargestIdx(&rowText, startingDigit, ignoringIds);

            possibleMatches.push_back(firstLargestIdx);
            ignoringIds[batteryIdx] = firstLargestIdx;

            
            if (startingDigit == 0) {
                startingDigit = firstLargestIdx;
            }
        }

        std::sort(possibleMatches.begin(), possibleMatches.end());
        // use largest left to right
        long long  largestBatteryPack = 0;
        for (int digit = 12; digit > 0; digit--) {
            int digitValue = rowText[possibleMatches[12 - digit]] - '0';
            largestBatteryPack += (long long )digitValue*(long long)(pow(10, digit - 1));
        }

        std::cout << largestBatteryPack << "\n";
        voltageSum += largestBatteryPack;
    }
    // Printing the output
    std::cout << voltageSum << "\n";

    PuzzleInput.close();
}