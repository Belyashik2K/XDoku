//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef SUDOKUGAME_H
#define SUDOKUGAME_H

#include "SudokuGrid.h"
#include "enums/SudokuDifficulty.h"
#include "enums/SudokuGameStatus.h"
#include "models/custom_types/Timestamp.h"

class SudokuGame {
public:
    static SudokuGame startNewGame(int userId, SudokuDifficultyEnum difficulty);
    // SudokuGame loadGame(int gameId);
    void printInfo() const;
private:
    SudokuGame(
        int userId,
        SudokuGrid grid,
        SudokuGrid solutionGrid,
        SudokuDifficultyEnum difficulty
    );

    std::optional<int> id;
    int userId;
    SudokuGrid grid;
    SudokuGrid solutionGrid;
    SudokuDifficultyEnum difficulty;
    int mistakesCount;
    std::optional<Timestamp> startTime;
    std::optional<Timestamp> endTime;
    SudokuGameStatusEnum status;
    bool exitedWhilePlaying;
};

#endif //SUDOKUGAME_H
