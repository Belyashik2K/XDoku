//
// Created by Belyashik2K on 07.04.2025.
//

#include <utility>

#include "domain/sudoku/SudokuGame.h"

#include <format>

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

    if (value == solutionGrid.getCellValue(row, column)) {
        grid.setCellValue(row, column, value);
        move.setValid(true);
        grid.lockCell(row, column);
    } else {
        move.setValid(false);
        mistakesCount++;
    }

    moves.push_back(move);
    return move;
}

bool SudokuGame::isSudokuSolved() const {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (grid.getCellValue(row, col) != solutionGrid.getCellValue(row, col)) {
                return false;
            }
        }
    }
    return true;
}

int SudokuGame::getElapsedTime() const {
    if (endTime) {
        return endTime.value() - getStartTime().value();
    }
    return Timestamp::now() - getStartTime().value();
}

std::string SudokuGame::getElapsedTimeAsString() const {
    const int elapsedTime = getElapsedTime();
    int hours = elapsedTime / 3600;
    int minutes = elapsedTime % 3600 / 60;
    int seconds = elapsedTime % 60;
    std::string elapsed;
    if (hours) elapsed += std::format("{:02d}:", hours);
    elapsed += std::format("{:02d}:", minutes);
    elapsed += std::format("{:02d}", seconds);
    if (elapsed.empty()) elapsed = "00:00";
    return elapsed;
}

void SudokuGame::finish() {
    status = SudokuGameStatusEnum::FINISHED;
    endTime = Timestamp::now();
}

void SudokuGame::surrender() {
    status = SudokuGameStatusEnum::SURRENDERED;
    endTime = Timestamp::now();
}

