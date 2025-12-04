//
// Created by belyashik2k on 5/10/25.
//

#include "domain/sudoku/utils/SudokuFactory.h"

#include "application/managers/ProfilingManager.h"
#include "domain/sudoku/utils/SudokuGenerator.h"

std::unique_ptr<SudokuGame> SudokuGameFactory::createNewGame(int userId, SudokuDifficultyEnum difficulty) {
    FunctionTimerManager& manager = FunctionTimerManager::instance();
    SudokuGenerator generator;

    const auto [grid, solutionGrid] = manager.track(
        "SudokuGenerator::generate",
        [&generator](const SudokuDifficultyEnum difficulty) { return generator.generate(difficulty); },
        difficulty
    );

    return std::make_unique<SudokuGame>(
        userId,
        grid,
        solutionGrid,
        difficulty
    );
}
