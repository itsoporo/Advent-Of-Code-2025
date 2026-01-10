#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

const int directions[8][2] = {
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
    {0, -1},
    {-1, -1},
};

bool inBounds(const std::vector<std::vector<int>>& grid, int x, int y) {
    return 0 <= x && x < grid.size() && 0 <= y && y < grid[x].size();
}

int main() {
    // accessing the file using ifstream, writing is ofstream
    std::ifstream PuzzleInput("../inputs/Day4.txt");

    std::vector<std::vector<int>> grid;

    int movableRolls = 0;

    // showing grid
    std::string rowText;
    while (std::getline(PuzzleInput, rowText)) {
        std::vector<int> rowChar;
        for (int i = 0; i < rowText.size(); i++) {
            rowChar.push_back(rowText[i] == '@' ? 1 : 0);
        }
        
        grid.push_back(rowChar);
    }

    // checking every roll
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            if (grid[y][x] == 0) continue; // no point in checking non rolls

            int adjacentOccupied = 0;
            
            // check all 8 adjacents
            for (const auto& dir: directions) {
                int nextX = x + dir[0];
                int nextY = y + dir[1];
                if (!inBounds(grid, nextX, nextY)) continue;

                if (grid[nextY][nextX] == 1) {
                    adjacentOccupied++;
                }
            }

            // condition to move roll
            if (adjacentOccupied < 4) {
                movableRolls++;
            }
        }
    }

    // Printing the output
    std::cout << movableRolls << "\n";

    PuzzleInput.close();
}