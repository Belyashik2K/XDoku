//
// Created by belyashik2k on 5/10/25.
//

#include "domain/sudoku/utils/SudokuLoader.h"
#include "domain/sudoku/utils/SudokuSerializer.h"

SudokuGame SudokuGameLoader::loadGame(
    int id, int userId,
    const std::string &grid, const std::string &solutionGrid,
    const std::string &difficulty, int mistakesCount,
    const std::string &startTime, const std::optional<std::string> &endTime,
    const std::string &status
) {
    std::optional<Timestamp> endTimeOpt;
    if (!endTime.has_value()) {
        endTimeOpt = std::nullopt;
    } else {
        endTimeOpt = Timestamp(endTime.value());
    }

    return {
        id,
        userId,
        SudokuGridSerializer::loadGridFromJsonString(grid),
        SudokuGridSerializer::loadGridFromJsonString(solutionGrid),
        SudokuDifficulty::fromString(difficulty),
        mistakesCount,
        Timestamp(startTime),
        endTimeOpt,
        SudokuGameStatus::fromString(status)
    };
}
