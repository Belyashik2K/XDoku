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
    this->exitedWhilePlaying = false;
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
    std::cout << "Exited While Playing: " << (exitedWhilePlaying ? "Yes" : "No") << std::endl;

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