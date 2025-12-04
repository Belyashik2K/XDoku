//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef IMOVEREPOSITORY_H
#define IMOVEREPOSITORY_H
#include <vector>

#include "domain/sudoku/SudokuMove.h"

class IMoveRepository {
public:
    virtual ~IMoveRepository() = default;

    virtual bool createMove(
        const std::unique_ptr<SudokuMove>& move
    ) = 0;

    virtual bool createMoves(
        const std::vector<std::unique_ptr<SudokuMove>> &moves
    ) = 0;

};

#endif //IMOVEREPOSITORY_H
