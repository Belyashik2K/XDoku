//
// Created by belyashik2k on 5/10/25.
//

#ifndef SUDOKUFACTORY_H
#define SUDOKUFACTORY_H
#include "domain/sudoku/SudokuGame.h"

class SudokuGameFactory {
public:
    static SudokuGame createNewGame(int userId, SudokuDifficultyEnum difficulty);
};

#endif //SUDOKUFACTORY_H
