#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

int findLargestIdx(std::string *rowText, int startIdx, int ignoreIdx) {
    int largest = -1;
    int largestIdx = 0;
   
    // find right to left instead of left to right for case of 4040504
    for (int charIdx = startIdx; charIdx < (*rowText).size(); charIdx++) {
        if (charIdx == ignoreIdx) continue;

        int parsed = (*rowText)[charIdx] - '0';
        if (parsed > largest) {
            largest = parsed;
            largestIdx = charIdx;
        }
    }

    return largestIdx;
}

int main() {
    // accessing the file using ifstream, writing is ofstream
    std::ifstream PuzzleInput("../inputs/Day3.txt");

    int voltageSum = 0;

    std::string rowText;
    while (std::getline(PuzzleInput, rowText)) {
        int firstLargestIdx = findLargestIdx(&rowText, 0, -1);

        int secondLargestIdx = 0;
        if (firstLargestIdx == rowText.size() - 1) {
            secondLargestIdx = findLargestIdx(&rowText, 0, firstLargestIdx);
        } else {
            secondLargestIdx = findLargestIdx(&rowText, firstLargestIdx, firstLargestIdx);
        }

        int firstFound = (rowText[firstLargestIdx] - '0');
        int secondFound = (rowText[secondLargestIdx] - '0');

        // use largest left to right
        int largestBatteryPack = firstLargestIdx < secondLargestIdx ? firstFound*10 + secondFound : secondFound*10 + firstFound;

        voltageSum += largestBatteryPack;
    }
    // Printing the output
    std::cout << voltageSum << "\n";

    PuzzleInput.close();
}