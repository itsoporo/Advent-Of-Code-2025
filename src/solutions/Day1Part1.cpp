#include <iostream>
#include <fstream>
#include <string>

int main() {
    // accessing the file using ifstream, writing is ofstream
    std::ifstream PuzzleInput("Day1.txt");
    std::string myText;

    while (std::getline(PuzzleInput, myText)) {
        std::cout << myText;
    }

    


    // closing to prevent memory leaks
    PuzzleInput.close();
}