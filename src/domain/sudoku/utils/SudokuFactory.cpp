//
// Created by belyashik2k on 5/10/25.
//

#include "domain/sudoku/utils/SudokuFactory.h"

#include "domain/sudoku/utils/SudokuGenerator.h"

SudokuGame SudokuGameFactory::createNewGame(int userId, SudokuDifficultyEnum difficulty) {
    SudokuGenerator generator;
    const SudokuGrid grid = generator.generate(difficulty);
    const SudokuGrid solutionGrid = generator.getSolutionGrid(grid);

    return {userId, grid, solutionGrid, difficulty};
}
