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
        SudokuGameStatusEnum status,
        std::optional<std::vector<SudokuMove>> moves
    );

    SudokuMove createMove(int row, int column, int value);
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

    std::vector<SudokuMove> moves; // TODO: Replace with a vector of unique_ptr to SudokuMove

    void load_moves(const std::vector<SudokuMove> &stored_moves);
};

#endif //SUDOKUGAME_H
