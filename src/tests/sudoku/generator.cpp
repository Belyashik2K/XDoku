//
// Created by Belyashik2K on 07.04.2025.
//

#include <iostream>

#include "models/sudoku/utils/SudokuGenerator.h"

void testSudokuGenerator() {
    SudokuGenerator generator;

    std::vector difficulties = {
        SudokuDifficultyEnum::Easy,
        SudokuDifficultyEnum::Medium,
        SudokuDifficultyEnum::Hard,
        SudokuDifficultyEnum::Expert
    };

    for (const auto &difficulty : difficulties) {
        std ::cout << "Difficulty: " << static_cast<int>(difficulty) << std::endl;
        SudokuGrid grid = generator.generate(difficulty);
        SudokuGenerator::print(grid);
        std::cout << "==============================" << std::endl;
    }
}
