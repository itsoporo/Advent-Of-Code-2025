#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

bool hasTwin(long long id) {
    // is repeated twice
    int digits = log10l(id) + 1;
    if (digits%2 == 1) return false; // odds can't have it
    
    long long divisor = (long long)pow(10, digits/2);
    long long left = id/divisor;
    long long right = id%divisor;

    return left == right;
}

long long getInvalidIds(long long start, long long end) {
    long long sum = 0;
    
    for (long long i = start; i <= end; i++) {
        sum += hasTwin(i) ? i : 0;
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