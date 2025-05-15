//
// Created by Belyashik2K on 06.04.2025.
//

#include "domain/sudoku/enums/SudokuDifficulty.h"

#include <stdexcept>

#define TEST_CELL_COUNT 80
#define EASY_CELLS_COUNT 40
#define MEDIUM_CELLS_COUNT 36
#define HARD_CELLS_COUNT 32
#define EXPERT_CELLS_COUNT 28

int SudokuDifficulty::getOpenCellsCount(const SudokuDifficultyEnum level) {
    switch (level) {
        case SudokuDifficultyEnum::TEST:
            return TEST_CELL_COUNT;
        case SudokuDifficultyEnum::EASY:
            return EASY_CELLS_COUNT;
        case SudokuDifficultyEnum::MEDIUM:
            return MEDIUM_CELLS_COUNT;
        case SudokuDifficultyEnum::HARD:
            return HARD_CELLS_COUNT;
        case SudokuDifficultyEnum::EXPERT:
            return EXPERT_CELLS_COUNT;
        default:
            throw std::invalid_argument("Invalid difficulty level");
    }
}

std::string SudokuDifficulty::getDifficultyName(const SudokuDifficultyEnum level) {
    switch (level) {
        case SudokuDifficultyEnum::TEST:
            return "test";
        case SudokuDifficultyEnum::EASY:
            return "easy";
        case SudokuDifficultyEnum::MEDIUM:
            return "medium";
        case SudokuDifficultyEnum::HARD:
            return "hard";
        case SudokuDifficultyEnum::EXPERT:
            return "expert";
        default:
            throw std::invalid_argument("Invalid difficulty level");
    }
}

SudokuDifficultySettings SudokuDifficulty::getSettings(const SudokuDifficultyEnum level) {
    return SudokuDifficultySettings({getOpenCellsCount(level), getDifficultyName(level), getRatingMultiplier(level)});
}

SudokuDifficultyEnum SudokuDifficulty::fromString(const std::string &difficulty) {
    if (const auto it = sudokuDifficultyMap.find(difficulty); it != sudokuDifficultyMap.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid SudokuDifficultyEnum string value");
}

float SudokuDifficulty::getRatingMultiplier(const SudokuDifficultyEnum level) {
    switch (level) {
        case SudokuDifficultyEnum::TEST:
            return 100;
        case SudokuDifficultyEnum::EASY:
            return 1;
        case SudokuDifficultyEnum::MEDIUM:
            return 1.5;
        case SudokuDifficultyEnum::HARD:
            return 2;
        case SudokuDifficultyEnum::EXPERT:
            return 2.5;
        default:
            throw std::invalid_argument("Invalid difficulty level");
    }
}