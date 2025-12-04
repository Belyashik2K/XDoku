//
// Created by belyashik2k on 5/10/25.
//

#ifndef SUDOKULOADER_H
#define SUDOKULOADER_H

#include "domain/sudoku/SudokuGame.h"

class SudokuGameLoader {
public:
    static std::unique_ptr<SudokuGame> loadGame(
        int id,
        int userId,
        const std::string &grid,
        const std::string &solutionGrid,
        const std::string &difficulty,
        int mistakesCount,
        const std::string &startTime,
        const std::optional<std::string>& endTime,
        const std::string &status,
        std::optional<std::vector<std::unique_ptr<SudokuMove>>> moves = std::nullopt
    );

};

#endif //SUDOKULOADER_H
