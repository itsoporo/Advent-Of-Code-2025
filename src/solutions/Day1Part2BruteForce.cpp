#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // accessing the file using ifstream, writing is ofstream
    std::ifstream PuzzleInput("../inputs/Day1.txt");
    std::string rowText;

    // Puzzle says its starts at 50
    int dial = 50;
    int zeroMatches = 0;

    int startingAtZero = 0;
    while (std::getline(PuzzleInput, rowText)) {
        char dialDirection = rowText[0];
        int dialSpinAmount = std::stoi(&rowText[1]);
        
        // dial switching
        int spinDir = rowText[0] == 'R' ? 1 : -1;

        for (int i = 0; i < dialSpinAmount; i++) {
            dial += spinDir;
            if (dial == 100) {
                dial = 0;
            } else if (dial == -1) {
                dial = 99;
            }

            if (dial == 0) {
                zeroMatches++;
            }
        }
    }

    //Printing Out the solution

    std::cout << zeroMatches << "\n";

    // closing to prevent memory leaks
    PuzzleInput.close();
}