//
// Created by Belyashik2K on 06.04.2025.
//

#include "models/sudoku/enums/SudokuGameStatus.h"

#include <map>
#include <stdexcept>

std::string SudokuGameStatus::toString(const SudokuGameStatusEnum status) {
    switch (status) {
        case SudokuGameStatusEnum::IN_PROGRESS: return "in_progress";
        case SudokuGameStatusEnum::FINISHED: return "finished";
        case SudokuGameStatusEnum::SURRENDERED: return "surrendered";
        default: throw std::invalid_argument("Invalid SudokuGameStatusEnum value");
    }
}

SudokuGameStatusEnum SudokuGameStatus::fromString(const std::string &status) {
    static const std::map<std::string, SudokuGameStatusEnum> statusMap = {
        {"in_progress", SudokuGameStatusEnum::IN_PROGRESS},
        {"finished", SudokuGameStatusEnum::FINISHED},
        {"surrendered", SudokuGameStatusEnum::SURRENDERED}
    };

    if (const auto it = statusMap.find(status); it != statusMap.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid SudokuGameStatusEnum string value");
}
