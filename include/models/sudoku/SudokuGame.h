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
    int id;
    int userId;
    SudokuGrid grid;
    SudokuGrid solutionGrid;
    SudokuDifficultyEnum difficulty;
    int mistakesCount;
    Timestamp startTime;
    Timestamp endTime;
    SudokuGameStatusEnum status;
    bool exitedWhilePlaying;

public:
    SudokuGame();
    void startNewGame(int userId, SudokuDifficultyEnum difficulty);
};

#endif //SUDOKUGAME_H
