//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include <memory>

#include "SudokuGrid.h"
#include "SudokuMove.h"
#include "enums/SudokuDifficulty.h"
#include "enums/SudokuGameStatus.h"
#include "domain/custom_types/Timestamp.h"

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
        const std::optional<Timestamp> &endTime,
        SudokuGameStatusEnum status,
        const std::optional<std::vector<std::unique_ptr<SudokuMove>>> &moves
    );

    std::unique_ptr<SudokuMove> createMove(int row, int column, int value);
    bool isSudokuSolved() const;
    void finish();
    void surrender();

    [[nodiscard]] const SudokuGrid &getCurrentGrid() const { return grid; }
    [[nodiscard]] const SudokuGrid &getSolutionGrid() const { return solutionGrid; }
    [[nodiscard]] const SudokuDifficultyEnum &getDifficulty() const { return difficulty; }
    [[nodiscard]] const SudokuGameStatusEnum &getStatus() const { return status; }
    [[nodiscard]] const std::optional<Timestamp> &getStartTime() const { return startTime; }
    [[nodiscard]] int getMistakesCount() const { return mistakesCount; }
    [[nodiscard]] int getId() const { return id.value(); }
    [[nodiscard]] int getElapsedTime() const;
    [[nodiscard]] std::string getElapsedTimeAsString() const;
private:

    std::optional<int> id;
    int userId;
    SudokuGrid grid;
    SudokuGrid solutionGrid;
    SudokuDifficultyEnum difficulty;
    std::optional<Timestamp> startTime;
    std::optional<Timestamp> endTime;
    SudokuGameStatusEnum status;
    int mistakesCount = 0;

    // std::vector<std::unique_ptr<SudokuMove>> moves;

    void load_moves(const std::vector<std::unique_ptr<SudokuMove>> &stored_moves);
};

#endif //SUDOKUGAME_H
