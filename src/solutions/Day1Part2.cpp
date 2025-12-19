#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

int wrapAround(int num, int modulu) {
    return num < 0 ? (modulu + num%modulu)%modulu : num%modulu;
}

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

        if (rowText[0] == 'R') {
            // Moving right makes it easy
            zeroMatches += (dial + dialSpinAmount) / 100;
            dial = (dial + dialSpinAmount) % 100;
        } else {
            // two cases moving left

            if (dial > 0 && dialSpinAmount >= dial) {
                zeroMatches += 1 + (dialSpinAmount - dial) / 100;
            } else if (dial == 0 && dialSpinAmount >= 100) {
                zeroMatches += dialSpinAmount / 100;
            }
            dial = wrapAround(dial - dialSpinAmount, 100);
        }

        // std::cout << rowText << " At: " << dial << " " << zeroMatches << "\n";

    }

    //Printing Out the solution

    std::cout << zeroMatches << "\n";

    // closing to prevent memory leaks
    PuzzleInput.close();
}