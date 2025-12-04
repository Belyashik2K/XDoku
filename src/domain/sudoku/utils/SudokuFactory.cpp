//
// Created by belyashik2k on 5/10/25.
//

#include "domain/sudoku/utils/SudokuFactory.h"

#include "domain/sudoku/utils/SudokuGenerator.h"

std::unique_ptr<SudokuGame> SudokuGameFactory::createNewGame(int userId, SudokuDifficultyEnum difficulty) {
    SudokuGenerator generator;
    const auto [grid, solutionGrid] = generator.generate(difficulty);

    return std::make_unique<SudokuGame>(
        userId,
        grid,
        solutionGrid,
        difficulty
    );
}
