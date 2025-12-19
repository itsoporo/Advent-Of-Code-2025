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

    while (std::getline(PuzzleInput, rowText)) {
        char dialDirection = rowText[0];
        int dialSpinAmount = std::stoi(&rowText[1]);
        
        // dial switching
        if (rowText[0] == 'R') {
            dial = wrapAround(dial + dialSpinAmount, 100);
        } else {
            dial = wrapAround(dial - dialSpinAmount, 100);
        }

        // Password adding
        if (dial == 0) {
            zeroMatches++;
        }
    }

    //Printing Out the solution

    std::cout << zeroMatches;

    // closing to prevent memory leaks
    PuzzleInput.close();
}