//
// Created by Belyashik2K on 07.04.2025.
//

#include <utility>

#include "models/sudoku/SudokuGame.h"

#include <iostream>

#include "models/sudoku/utils/SudokuGenerator.h"

SudokuGame::SudokuGame(
    const int userId,
    SudokuGrid grid,
    SudokuGrid solutionGrid,
    const SudokuDifficultyEnum difficulty
): id(std::nullopt), startTime(std::nullopt), endTime(std::nullopt) {
    this->userId = userId;
    this->grid = std::move(grid);
    this->solutionGrid = std::move(solutionGrid);
    this->difficulty = difficulty;
    this->mistakesCount = 0;
    this->status = SudokuGameStatusEnum::IN_PROGRESS;
    this->exitedWhileSolved = false;
}

SudokuGame SudokuGame::startNewGame(
    const int userId,
    const SudokuDifficultyEnum difficulty
) {
    SudokuGenerator generator;
    const SudokuGrid grid = generator.generate(difficulty);
    const SudokuGrid solutionGrid = generator.getSolutionGrid(grid);

    return SudokuGame(userId, grid, solutionGrid, difficulty);
}

void SudokuGame::printInfo() const {
    std::cout << "User ID: " << userId << std::endl;
    std::cout << "Difficulty: " << static_cast<int>(difficulty) << std::endl;
    std::cout << "Mistakes Count: " << mistakesCount << std::endl;
    std::cout << "Status: " << static_cast<int>(status) << std::endl;
    if (startTime.has_value()) {
        std::cout << "Start Time: " << startTime.value().toString() << std::endl;
    } else {
        std::cout << "Start Time: Not set" << std::endl;
    }
    if (endTime.has_value()) {
        std::cout << "End Time: " << endTime.value().toString() << std::endl;
    } else {
        std::cout << "End Time: Not set" << std::endl;
    }
    std::cout << "Exited While Playing: " << (exitedWhileSolved ? "Yes" : "No") << std::endl;

    std::cout << "===============================" << std::endl;
    std::cout << "Grid:" << std::endl;
    SudokuGrid grid = this->grid;
    SudokuGenerator::print(grid);
    std::cout << "===============================" << std::endl;
    std::cout << "Solution Grid:" << std::endl;
    SudokuGrid solutionGrid = this->solutionGrid;
    SudokuGenerator::print(solutionGrid);
    std::cout << "===============================" << std::endl;
}

std::pair<nlohmann::json, nlohmann::json> SudokuGame::getGridsAsJson() const {
    nlohmann::json gridJson = nlohmann::json::array();
    nlohmann::json solutionGridJson = nlohmann::json::array();

    for (int i = 0; i < 9; ++i) {
        nlohmann::json row;
        nlohmann::json solutionRow;
        for (int j = 0; j < 9; ++j) {
            row.push_back(grid.getCells()[i][j].getValue());
            solutionRow.push_back(solutionGrid.getCells()[i][j].getValue());
        }
        gridJson.push_back(row);
        solutionGridJson.push_back(solutionRow);
    }
    return std::make_pair(gridJson, solutionGridJson);
}

std::string SudokuGame::getDifficultyAsString() const {
    return SudokuDifficulty::getSettings(difficulty).difficultyName;
}

SudokuDifficultyEnum SudokuGame::loadDifficultyFromString(const std::string &difficulty) {
    return SudokuDifficulty::fromString(difficulty);
}

SudokuGameStatusEnum SudokuGame::loadStatusFromString(const std::string &status) {
    return SudokuGameStatus::fromString(status);
}

void SudokuGame::loadGridsFromString(const std::string &grid, const std::string &solutionGrid) {
    nlohmann::json gridJson = nlohmann::json::parse(grid);
    nlohmann::json solutionGridJson = nlohmann::json::parse(solutionGrid);

    auto &gridCells = this->grid.getCells();
    auto &solutionCells = this->solutionGrid.getCells();

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            gridCells[i][j].setValue(gridJson[i][j].get<int>());
            solutionCells[i][j].setValue(solutionGridJson[i][j].get<int>());
        }
    }
}

SudokuGame::SudokuGame(
    int id,
    const int userId,
    const std::string &grid,
    const std::string &solutionGrid,
    const std::string &difficulty,
    const int mistakesCount,
    std::string startTime,
    const std::optional<std::string> &endTime,
    const std::string &status,
    const bool exitedWhileSolved
): id(id), userId(userId), mistakesCount(mistakesCount), startTime(startTime), endTime(endTime),
   exitedWhileSolved(exitedWhileSolved) {
    this->grid = SudokuGrid();
    this->solutionGrid = SudokuGrid();
    loadGridsFromString(grid, solutionGrid);
    this->difficulty = loadDifficultyFromString(difficulty);
    this->status = loadStatusFromString(status);
}

SudokuGame SudokuGame::loadGame(
    const int id,
    const int userId,
    const std::string &grid,
    const std::string &solutionGrid,
    const std::string &difficulty,
    const int mistakesCount,
    const std::string &startTime,
    const std::optional<std::string> &endTime,
    const std::string &status,
    const bool exitedWhileSolved
) {
    return SudokuGame(
        id,
        userId,
        grid,
        solutionGrid,
        difficulty,
        mistakesCount,
        startTime,
        endTime,
        status,
        exitedWhileSolved
    );
}
