#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

long long spliceLong(long long num, int spliceStart, int length) { // from right to left
    long long startDivisor = (long long)pow(10, spliceStart);
    long long lengthDivisor = (long long)pow(10, length);

    long long leftSide = num/startDivisor; // removing the left digits
    long long clippedLeft = leftSide%lengthDivisor; // removing the right digits

    return clippedLeft;
}

bool hasRepeating(long long id) {
    // is repeated twice
    int digits = log10l(id) + 1;
    
    for (int splits = 2; splits <= digits; splits++) {
        if (digits%splits != 0) { continue; } // if we can even split it evenly

        long long previousPiece = -1;
        bool failed = false;

        for (int piece = 0; piece < splits; piece++) {
            int splitLength = digits/splits;
            long long currentPiece = spliceLong(id, piece*splitLength, splitLength);

            if (previousPiece == -1 || previousPiece == currentPiece) {
                previousPiece = currentPiece;
            } else {
                failed = true; // the repeat failed
                break; // no points in getting the rest
            }
        }

        if (!failed) {
            return true;
        }
    }

    return false; // found no repeats
}

long long getInvalidIds(long long start, long long end) {
    long long sum = 0;
    
    for (long long i = start; i <= end; i++) {
        sum += hasRepeating(i) ? i : 0;
    }

    return sum;
}

int main() {
    // accessing the file using ifstream, writing is ofstream
    std::ifstream PuzzleInput("../inputs/Day2.txt");

    long long invalidIds = 0;

    std::string rowText;
    while (std::getline(PuzzleInput, rowText)) {
        size_t startPos = 0;

        while (startPos < rowText.size()) {
            // input split by commas and dashes
            size_t colonPos = rowText.find("-", startPos);
            size_t commaPos = rowText.find(",", startPos);
            // because then we have to find commans it would ignore the last range
            if (commaPos == std::string::npos) { 
                commaPos = rowText.size();
            }

            if (colonPos == std::string::npos) {
                break;
            }

            std::string startRange = rowText.substr(startPos, colonPos - startPos);
            std::string endRange = rowText.substr(colonPos + 1, commaPos - (colonPos + 1));

            invalidIds += getInvalidIds(std::stoll(startRange), std::stoll(endRange));

            startPos = commaPos + 1;
        }
    }

    // Printing the output
    std::cout << invalidIds << "\n";

    PuzzleInput.close();
}