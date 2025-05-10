//
// Created by Belyashik2K on 07.04.2025.
//

#include <utility>

#include "domain/sudoku/SudokuGame.h"
#include "domain/sudoku/utils/SudokuGenerator.h"

SudokuGame::SudokuGame(
    const int userId,
    SudokuGrid grid,
    SudokuGrid solutionGrid,
    const SudokuDifficultyEnum difficulty
) {
    this->userId = userId;
    this->grid = std::move(grid);
    this->solutionGrid = std::move(solutionGrid);
    this->difficulty = difficulty;
    this->mistakesCount = 0;
    this->status = SudokuGameStatusEnum::IN_PROGRESS;
}

SudokuGame::SudokuGame(
    int id, const int userId, SudokuGrid grid, SudokuGrid solutionGrid,
    const SudokuDifficultyEnum difficulty, const int mistakesCount,
    Timestamp startTime, std::optional<Timestamp> endTime,
    const SudokuGameStatusEnum status
) {
    this->id = id;
    this->userId = userId;
    this->grid = std::move(grid);
    this->solutionGrid = std::move(solutionGrid);
    this->difficulty = difficulty;
    this->mistakesCount = mistakesCount;
    this->startTime = startTime;
    this->endTime = endTime;
    this->status = status;
}

SudokuMove SudokuGame::createMove(
    const int row,
    const int column,
    const int value
) {
    if (!id) {
        throw std::runtime_error("Game ID is not set");
    }

    SudokuMove move(id.value(), row, column, value);

    if (!grid.setCellValue(row, column, value)) {
        move.setValid(false);
        mistakesCount++;
        return move;
    }

    if (grid.getCellValue(row, column) == solutionGrid.getCellValue(row, column)) {
        grid.lockCell(row, column);
        move.setValid(true);
    } else {
        move.setValid(false);
        mistakesCount++;
    }

    moves.push_back(move);
    return move;
}
