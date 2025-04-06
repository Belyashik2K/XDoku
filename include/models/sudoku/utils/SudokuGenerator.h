//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H

#include "models/sudoku/SudokuGrid.h"
#include "models/sudoku/enums/SudokuDifficulty.h"

class SudokuGenerator {
public:
    static SudokuGrid generate(SudokuDifficultyEnum difficulty);
private:
    static void removeNumbers(SudokuGrid &grid, int count);
    static bool hasUniqueSolution(const SudokuGrid &grid);
};

#endif //SUDOKUGENERATOR_H
