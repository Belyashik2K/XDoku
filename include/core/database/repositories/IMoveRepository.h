//
// Created by Belyashik2K on 06.04.2025.
//

#ifndef IMOVEREPOSITORY_H
#define IMOVEREPOSITORY_H
#include "models/sudoku/SudokuMove.h"

class IMoveRepository {
public:
    virtual ~IMoveRepository() = default;

    virtual bool createMove(
        SudokuMove move
    ) = 0;
};

#endif //IMOVEREPOSITORY_H
