//
// Created by Belyashik2K on 06.04.2025.
//

#include "models/sudoku/enums/SudokuDifficulty.h"

#include <stdexcept>

#define EASY_CELLS_COUNT 40
#define MEDIUM_CELLS_COUNT 36
#define HARD_CELLS_COUNT 32
#define EXPERT_CELLS_COUNT 28

int SudokuDifficulty::getOpenCellsCount(const SudokuDifficultyEnum level) {
    switch (level) {
        case SudokuDifficultyEnum::Easy:
            return EASY_CELLS_COUNT;
        case SudokuDifficultyEnum::Medium:
            return MEDIUM_CELLS_COUNT;
        case SudokuDifficultyEnum::Hard:
            return HARD_CELLS_COUNT;
        case SudokuDifficultyEnum::Expert:
            return EXPERT_CELLS_COUNT;
        default:
            throw std::invalid_argument("Invalid difficulty level");
    }
}

SudokuDifficultySettings SudokuDifficulty::getSettings(const SudokuDifficultyEnum level) {
    return SudokuDifficultySettings({getOpenCellsCount(level)});
}
