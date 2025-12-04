//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H

#include <vector>
#include <set>
#include <array>
#include <random>

#include "domain/sudoku/SudokuGrid.h"
#include "domain/sudoku/enums/SudokuDifficulty.h"

class SudokuGenerator {
public:
    std::pair<SudokuGrid, SudokuGrid> generate(SudokuDifficultyEnum difficulty);
private:
    std::pair<SudokuGrid, SudokuGrid> generateGrid(int open_cells_count);

    static bool hasUniqueSolution(const SudokuGrid &grid);

    static bool solveWithLimit(SudokuGrid &grid, int &solutions, int limit = 2);

    static void buildMasksFromGrid(
        const SudokuGrid &grid,
        std::array<int, 9> &rowMask,
        std::array<int, 9> &colMask,
        std::array<int, 9> &boxMask
    );

    bool applyRemoval(SudokuGrid &puzzle, int targetRemovals, std::mt19937 &rng);
};

#endif //SUDOKUGENERATOR_H
