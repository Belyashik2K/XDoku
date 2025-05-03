//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include "SudokuGrid.h"
#include "enums/SudokuDifficulty.h"
#include "enums/SudokuGameStatus.h"
#include "models/custom_types/Timestamp.h"
#include "json.hpp"
#include "SudokuMove.h"

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

    void printInfo();
    std::pair<nlohmann::json, nlohmann::json> getGridsAsJson() const;
    std::string getDifficultyAsString() const;
    bool addMove(const SudokuMove &move);
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

    std::optional<std::vector<SudokuMove>> moves; // Replace with a vector of unique_ptr to SudokuMove

    void loadGridsFromString(
        const std::string &grid,
        const std::string &solutionGrid
    );

    void actualizeCurrentGrid();

    static SudokuDifficultyEnum loadDifficultyFromString(const std::string &difficulty);

    static SudokuGameStatusEnum loadStatusFromString(const std::string &status);
};

#endif //SUDOKUGAME_H
