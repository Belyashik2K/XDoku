//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include "SudokuGrid.h"
#include "SudokuMove.h"
#include "enums/SudokuDifficulty.h"
#include "enums/SudokuGameStatus.h"
#include "domain/custom_types/Timestamp.h"

#include "json.hpp"

class SudokuGame {
public:
    SudokuGame(
        int userId,
        SudokuGrid grid,
        SudokuGrid solutionGrid,
        SudokuDifficultyEnum difficulty
    );

    SudokuGame(
        int id,
        int userId,
        SudokuGrid grid,
        SudokuGrid solutionGrid,
        SudokuDifficultyEnum difficulty,
        int mistakesCount,
        Timestamp startTime,
        std::optional<Timestamp> endTime,
        SudokuGameStatusEnum status
    );

    SudokuMove createMove(int row, int column, int value);

    [[nodiscard]] const SudokuGrid &getCurrentGrid() const { return grid; }
    [[nodiscard]] const SudokuGrid &getSolutionGrid() const { return solutionGrid; }
    [[nodiscard]] const SudokuDifficultyEnum &getDifficulty() const { return difficulty; }
    [[nodiscard]] const SudokuGameStatusEnum &getStatus() const { return status; }
    [[nodiscard]] int getId() const { return id.value(); }
private:

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
    SudokuGrid solutionGrid;
    SudokuDifficultyEnum difficulty;
    std::optional<Timestamp> startTime;
    std::optional<Timestamp> endTime;
    SudokuGameStatusEnum status;
    int mistakesCount = 0;

    std::vector<SudokuMove> moves; // TODO: Replace with a vector of unique_ptr to SudokuMove
};

#endif //SUDOKUGAME_H
