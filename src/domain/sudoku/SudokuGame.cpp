//
// Created by Belyashik2K on 07.04.2025.
//

#include <format>
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
    int id,
    const int userId,
    SudokuGrid grid,
    SudokuGrid solutionGrid,
    const SudokuDifficultyEnum difficulty,
    const int mistakesCount,
    Timestamp startTime,
    const std::optional<Timestamp> &endTime,
    const SudokuGameStatusEnum status,
    const std::optional<std::vector<std::unique_ptr<SudokuMove>>> &moves
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

    if (moves.has_value()) {
        load_moves(moves.value());
    }
}

void SudokuGame::load_moves(const std::vector<std::unique_ptr<SudokuMove>> &stored_moves) {
    for (const auto &move: stored_moves) {
        const int row = move->coords().first;
        const int col = move->coords().second;
        const int value = move->getValue();

        if (move->isValidMove()) {
            grid.setCellValue(row, col, value);
            grid.lockCell(row, col);
        } else {
            mistakesCount++;
        }
        // this->moves.push_back(std::make_unique<SudokuMove>(*move));
    }
}


std::unique_ptr<SudokuMove> SudokuGame::createMove(
    const int row,
    const int column,
    const int value
) {
    if (!id) {
        throw std::runtime_error("Game ID is not set");
    }

    auto move = std::make_unique<SudokuMove>(id.value(), row, column, value);

    if (value == solutionGrid.getCellValue(row, column)) {
        grid.setCellValue(row, column, value);
        move->setValid(true);
        grid.lockCell(row, column);
    } else {
        move->setValid(false);
        mistakesCount++;
    }

    // moves.push_back(std::move(move));
    return move;
}

bool SudokuGame::isSudokuSolved() const {
    return grid.isGridSolved();
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

