//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include "SudokuGrid.h"
#include "enums/SudokuDifficulty.h"
#include "enums/SudokuGameStatus.h"
#include "json.hpp"
#include "SudokuMove.h"
#include "domain/custom_types/Timestamp.h"

class SudokuGame {
public:
    static SudokuGame startNewGame(int userId, SudokuDifficultyEnum difficulty);
    static SudokuGame loadGame(
        int id,
        int userId,
        const std::string &grid,
        const std::string &solutionGrid,
        const std::string &difficulty,
        int mistakesCount,
        const std::string &startTime,
        const std::optional<std::string> &endTime,
        const std::string &status,
        bool exitedWhileSolved
    );

    SudokuMove createMove(int row, int column, int value);
    void actualizeCurrentGrid();

    void printInfo();
    [[nodiscard]] std::pair<nlohmann::json, nlohmann::json> getGridsAsJson() const;
    [[nodiscard]] std::string getDifficultyAsString() const;

    [[nodiscard]] const SudokuGrid *getCurrentGrid() const { return &currentGrid; }
    [[nodiscard]] int getId() const { return id.value(); }
private:
    SudokuGame(
        int userId,
        SudokuGrid grid,
        SudokuGrid solutionGrid,
        SudokuDifficultyEnum difficulty
    );

    SudokuGame(
        int id,
        int userId,
        const std::string &grid,
        const std::string &solutionGrid,
        const std::string &difficulty,
        int mistakesCount,
        std::string startTime,
        const std::optional<std::string> &endTime,
        const std::string &status,
        bool exitedWhileSolved
    );

    std::optional<int> id;
    int userId;
    SudokuGrid grid;
    SudokuGrid currentGrid;
    SudokuGrid solutionGrid;
    SudokuDifficultyEnum difficulty;
    int mistakesCount;
    std::optional<Timestamp> startTime;
    std::optional<Timestamp> endTime;
    SudokuGameStatusEnum status;
    bool exitedWhileSolved;

    std::optional<std::vector<SudokuMove>> moves; // TODO: Replace with a vector of unique_ptr to SudokuMove

    void loadGridsFromString(
        const std::string &grid,
        const std::string &solutionGrid
    );

    static SudokuDifficultyEnum loadDifficultyFromString(const std::string &difficulty);

    static SudokuGameStatusEnum loadStatusFromString(const std::string &status);
};

#endif //SUDOKUGAME_H
