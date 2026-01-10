#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <array>

using Point = std::array<int, 2>;
using PointList = std::vector<Point>;

const int directions[8][2] = {
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1},
    {1, 0}, {1, -1}, {0, -1}, {-1, -1},
};

bool inBounds(const std::vector<std::vector<int>>& grid, int x, int y) {
    return 0 <= x && x < grid.size() && 0 <= y && y < grid[x].size();
}

int main() {
    // accessing the file using ifstream, writing is ofstream
    std::ifstream PuzzleInput("../inputs/Day4.txt");

    std::vector<std::vector<int>> grid;

    int rollsRemoved = 0;

    // showing grid
    std::string rowText;
    while (std::getline(PuzzleInput, rowText)) {
        std::vector<int> rowChar;
        for (char c: rowText) {
            rowChar.push_back(c == '@' ? 1 : 0);
        }
        
        grid.push_back(std::move(rowChar));
    }

    // checking every roll
    while (true) {
        PointList toBeRemoved;

        // loop through whole grid points
        for (int y = 0; y < grid.size(); y++) {
            for (int x = 0; x < grid[y].size(); x++) {
                if (grid[y][x] == 0) continue; // no point in checking non rolls

                int adjacentOccupied = 0;
                
                // check all 8 adjacents
                for (const auto& [dy, dx]: directions) {
                    int nextX = x + dy;
                    int nextY = y + dx;

                    if (!inBounds(grid, nextX, nextY)) continue;

                    if (grid[nextY][nextX] == 1) {
                        adjacentOccupied++;
                    }
                }

                // condition to move roll
                if (adjacentOccupied < 4) {
                    toBeRemoved.push_back({y, x}); // its rows then columns
                }
            }
        }

        if (toBeRemoved.empty()) break;

        for (const auto& [py, px]: toBeRemoved) {
            grid[py][px] = 0;
        }

        rollsRemoved += toBeRemoved.size();
    }

    // Printing the output
    std::cout << rollsRemoved << "\n";

    PuzzleInput.close();
}