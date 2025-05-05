//
// Created by Belyashik2K on 06.04.2025.
//

#include "domain/sudoku/enums/SudokuDifficulty.h"

#include <map>
#include <stdexcept>

#define EASY_CELLS_COUNT 40
#define MEDIUM_CELLS_COUNT 36
#define HARD_CELLS_COUNT 32
#define EXPERT_CELLS_COUNT 28

int SudokuDifficulty::getOpenCellsCount(const SudokuDifficultyEnum level) {
    switch (level) {
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
    return SudokuDifficultySettings({getOpenCellsCount(level), getDifficultyName(level)});
}

SudokuDifficultyEnum SudokuDifficulty::fromString(const std::string &difficulty) {
    static const std::map<std::string, SudokuDifficultyEnum> difficultyMap = {
        {"easy", SudokuDifficultyEnum::EASY},
        {"medium", SudokuDifficultyEnum::MEDIUM},
        {"hard", SudokuDifficultyEnum::HARD},
        {"expert", SudokuDifficultyEnum::EXPERT}
    };

    if (const auto it = difficultyMap.find(difficulty); it != difficultyMap.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid SudokuDifficultyEnum string value");
}
